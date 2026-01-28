#!/bin/bash

# Define paths
CONF_DIR="/etc/environment.d"
CONF_FILE="$CONF_DIR/kywc-7a2000.conf"

# Ensure the configuration directory exists
if [ ! -d "$CONF_DIR" ]; then
  mkdir -p "$CONF_DIR"
fi

# Get all VGA controllers (Class 0300)
# Example output line: 00:06.1 0300: 0014:7a36 (rev 02)
gpu_list=$(lspci -n | grep "0300:")

if [ -z "$gpu_list" ]; then
  echo "No GPU detected."
  exit 1
fi

# Count total number of GPUs found
total_gpus=$(echo "$gpu_list" | wc -l)

# Count how many of those GPUs match the specific integrated IDs (7a36:0014 or 7a26:0014)
# We use -E for extended regex to match either ID
matched_integrated_count=$(echo "$gpu_list" | grep -Ec "0014:7a36")

echo "Total GPUs found: $total_gpus"
echo "Integrated GPUs matched: $matched_integrated_count"

# Logic: Only use pixman if ALL detected GPUs are the specified integrated ones
# This ensures that if a discrete GPU is plugged in, the condition fails.
if [ "$total_gpus" -eq "$matched_integrated_count" ] && [ "$total_gpus" -gt 0 ]; then
  echo "Pure integrated GPU environment detected. Setting KYWC_RENDERER=pixman..."
  echo "KYWC_RENDERER=pixman" >"$CONF_FILE"
else
  echo "Discrete GPU detected or multiple mixed GPUs found. Disabling pixman renderer..."
  # Clear the config file
  : >"$CONF_FILE"
fi

echo "Done. Configuration saved to $CONF_FILE"
