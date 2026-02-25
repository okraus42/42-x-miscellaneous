import sys
import time
import shutil
import termios
import tty
import math

# Fake file names
files = [
    "a.txt",
    "report_final.docx",
    "very_long_filename_for_testing_purposes.log",
    "data.csv",
    "image_backup_2024_01_15.png",
    "notes.md",
    "presentation_v2.pptx",
    "archive.tar.gz",
    "script.py",
    "database_dump.sql",
    "summary.pdf",
    "photo.jpg",
    "config.yaml",
    "music_track.mp3",
    "video_recording.mp4",
    "spreadsheet.xlsx",
    "temp_file.tmp",
    "readme.txt",
    "docker-compose.yml",
    "final_version_really_final_this_time.zip"
]

spinner = ["|", "/", "-", "\\"]
bar_width = 40

# ANSI sequences
ALT_BUFFER_ON  = "\033[?1049h"
ALT_BUFFER_OFF = "\033[?1049l"
CLEAR_SCREEN   = "\033[2J"
HIDE_CURSOR    = "\033[?25l"
SHOW_CURSOR    = "\033[?25h"

def move(row, col=1):
    return f"\033[{row};{col}H"

def wait_for_esc():
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        while True:
            if sys.stdin.read(1) == "\x1b":  # ESC
                break
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)

def clear_lines_from(row, line_count):
    """Clear line_count lines starting at row"""
    for i in range(line_count):
        sys.stdout.write(move(row + i, 1) + "\033[2K")

# Enter alternate screen
sys.stdout.write(ALT_BUFFER_ON)
sys.stdout.write(HIDE_CURSOR)
sys.stdout.write(CLEAR_SCREEN)

# Title on row 1
sys.stdout.write(move(1, 1) + "PROGRESS BAR DEMONSTRATION")
sys.stdout.flush()

total = len(files)
spin_index = 0
progress_row = 3  # always write progress bar here

for i, f in enumerate(files, 1):
    sleep_time = len(f) * 0.03
    steps = max(1, int(sleep_time / 0.05))

    for _ in range(steps):
        percent = int(((i - 1) / total) * 100)
        filled = int(bar_width * (i - 1) / total)
        bar = "#" * filled + "-" * (bar_width - filled)
        spin = spinner[spin_index % len(spinner)]

        line = f"[{spin}] [{bar}] [{percent:3d}%] Processing: {f}"

        # Determine how many lines this string would occupy
        cols = shutil.get_terminal_size().columns
        rows_needed = max(1, math.ceil(len(line) / cols))

        # Clear all those lines before writing
        clear_lines_from(progress_row, rows_needed)

        # Original writing logic (unchanged)
        sys.stdout.write(move(progress_row, 1))
        sys.stdout.write(line)
        sys.stdout.flush()

        spin_index += 1
        time.sleep(sleep_time / steps)

    # Final render for the file
    percent = int((i / total) * 100)
    filled = int(bar_width * i / total)
    bar = "#" * filled + "-" * (bar_width - filled)
    spin = spinner[spin_index % len(spinner)]
    line = f"[{spin}] [{bar}] [{percent:3d}%] Processing: {f}"

    rows_needed = max(1, math.ceil(len(line) / cols))
    clear_lines_from(progress_row, rows_needed)
    sys.stdout.write(move(progress_row, 1))
    sys.stdout.write(line)
    sys.stdout.flush()
    spin_index += 1

# Finished message on row 5
sys.stdout.write(move(progress_row + 2, 1) + "Done! Press ESC to exit...")
sys.stdout.flush()

wait_for_esc()

# Restore terminal
sys.stdout.write(SHOW_CURSOR)
sys.stdout.write(ALT_BUFFER_OFF)
sys.stdout.flush()
