# YADL

Yet Another Discord Library

### Voice
1. Type `!!voice [voice_channel_id]` any guild text channel.
2. A FIFO pipe that named guild id would have been created in a directory with `test_yadl`.
3. Send the `s16le` audio data to the pipe, the bot will play the audio. <br>

e.g.
```bash
youtube-dl --quiet -f bestaudio "[Youtube Video URL]" -o - | ffmpeg  -i pipe: -f s16le -ac 2 -ar 48000 -acodec pcm_s16le - | > ./928872876965249065.pipe
```