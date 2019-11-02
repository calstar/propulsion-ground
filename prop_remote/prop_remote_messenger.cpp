

class prop_remote_messenger
{
    private:
        const int FLATBUF_BUF_SIZE = 256;
        uint8_t flatbuf_buffer[FLATBUF_BUF_SIZE];
        unsigned int buffer_len;

    prop_remote_messenger(){
        buffer_len = 0;
    }

    void update_fc_buf(char c){
        if (buffer_len == FLATBUF_BUF_SIZE) {
            // If at end of buffer, shift and add to end
            memmove(buffer, buffer + 1, FLATBUF_BUF_SIZE - 1);
            buffer[FLATBUF_BUF_SIZE - 1] = (uint8_t)c;
        } else {
            // Otherwise build up buffer
            buffer[buffer_len++] = (uint8_t)c;
        }
    }
}
