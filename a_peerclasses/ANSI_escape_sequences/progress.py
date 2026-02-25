import time
import sys

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
bar_width = 30

# ANSI sequences
CURSOR_TO_START = "\033[1G"
CLEAR_LINE = "\033[2K"

def draw_progress(done, total, filename, spin_index):
    percent = int((done / total) * 100)
    filled = int(bar_width * done / total)
    bar = "#" * filled + "-" * (bar_width - filled)
    spin = spinner[spin_index % len(spinner)]

    line = f"[{spin}] [{bar}] [{percent:3d}%] Processing: {filename}"

    sys.stdout.write(CURSOR_TO_START + CLEAR_LINE + line)
    sys.stdout.flush()

total = len(files)
spin_index = 0

for i, f in enumerate(files, 1):
    sleep_time = len(f) * 0.02
    steps = max(1, int(sleep_time / 0.2))

    for _ in range(steps):
        draw_progress(i - 1, total, f, spin_index)
        spin_index += 1
        time.sleep(sleep_time / steps)

    draw_progress(i, total, f, spin_index)
    spin_index += 1

# Move to next line after completion
sys.stdout.write("\nDone!\n")
