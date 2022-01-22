# YADL
Yet Another Discord Library

### Building
#### Requirements
```bash
libm libz libdl pthread openssl libopus libsodium libwebsockets libcap(linux only)
```

1. create a `build` directory at the project root directory.
2. enter `build` directory.
3. `cmake ..` and `make` to build YADL library.

### Test codes
#### Voice Connection
1. Type `!!connect [voice_channel_id]` any guild text channel.
2. A FIFO pipe that named guild id would have been created in a directory with `test_yadl`.
3. Send the `s16le` audio data to the pipe, the bot will play the audio. <br>
    ```bash
    youtube-dl --quiet -f bestaudio "[Youtube Video URL]" -o - | ffmpeg  -i pipe: -f s16le -ac 2 -ar 48000 -acodec pcm_s16le - > ./928872876965249065.pipe
    ```
4. Type `!!disconnect` to disconnect from the voice channel.
