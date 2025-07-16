# GStreamer Video Display - Command Line and C Example

This repository demonstrates how to build a **basic GStreamer pipeline** to display video from a file, using:

- GStreamer command-line tool (`gst-launch-1.0`)
- A C program using the GStreamer API

---

## 🔧 Requirements

- GStreamer (version 1.0+)
- gcc (for compiling C code)
- A sample video file (e.g., `sample.mp4`)

---

## 🎬 Command Line Example

You can display a video using a one-liner GStreamer command:

```bash
gst-launch-1.0 filesrc location=sample.mp4 ! decodebin ! videoconvert ! autovideosink
