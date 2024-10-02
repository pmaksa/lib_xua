import re

def parse_vcd(file_path):
    """
    Parse the VCD file and extract signal values.
    
    :param file_path: Path to the VCD file.
    :return: Dictionary containing signals and their corresponding binary values over time.
    """
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    time = None
    signals = {}
    signal_map = {}
    
    # Regex patterns
    time_pattern = re.compile(r"^#(\d+)")  # Match time changes
    value_change_pattern = re.compile(r"^([01xz])(\S+)")  # Match single-bit value changes
    binary_value_change_pattern = re.compile(r"^b([01xz]+)\s+(\S+)")  # Match multi-bit value changes
    signal_def_pattern = re.compile(r"^\$var\s+\w+\s+\d+\s+(\S+)\s+(\S+)\s+\$end")  # Match signal definitions
    
    for line in lines:
        line = line.strip()
        
        # Match time changes
        match_time = time_pattern.match(line)
        if match_time:
            time = match_time.group(1)
            continue
        
        # Match signal definitions
        match_signal_def = signal_def_pattern.match(line)
        if match_signal_def:
            signal_id = match_signal_def.group(1)
            signal_name = match_signal_def.group(2)
            signal_map[signal_id] = signal_name
            signals[signal_name] = []
            continue
        
        # Match single-bit value changes (e.g., '1signal' or '0signal')
        match_value_change = value_change_pattern.match(line)
        if match_value_change:
            value = match_value_change.group(1)
            signal_id = match_value_change.group(2)
            if signal_id in signal_map:
                signal_name = signal_map[signal_id]
                signals[signal_name].append((time, value))
            continue
        
        # Match multi-bit binary value changes (e.g., 'b1010 signal')
        match_binary_value_change = binary_value_change_pattern.match(line)
        if match_binary_value_change:
            binary_value = match_binary_value_change.group(1)
            value = str(int(binary_value, 2))
            signal_id = match_binary_value_change.group(2)
            if signal_id in signal_map:
                signal_name = signal_map[signal_id]
                signals[signal_name].append((time, value))
            continue
    
    return signals

def print_signal_values(signals):
    """
    Print the extracted binary values for each signal.
    
    :param signals: Dictionary of signal binary values over time.
    """
    for signal, values in signals.items():
        print(f"Signal: {signal}")
        old_time = 0
        counter = 0
        for time, value in values:
            time = int(time)
            if counter == 0:
                print(f"  Time: {time}, Value: {value}")
            else:
                diff = time - old_time
                print(f"  Time: {time}, Value: {value}, Diff: {diff}")
                # if diff > 3080: print("****")
            counter += 1
            old_time = time
        print()

# Example usage
if __name__ == "__main__":
    vcd_file = 'xscope_log.vcd'  # Replace with your VCD file path
    signals = parse_vcd(vcd_file)
    print_signal_values(signals)
