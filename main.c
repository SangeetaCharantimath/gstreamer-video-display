#include <gst/gst.h>

int main(int argc, char *argv[]) {
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    gst_init(&argc, &argv);

    // Check for input file argument
    if (argc != 2) {
        g_printerr("Usage: %s <video file path>\n", argv[0]);
        return -1;
    }

    // Build the pipeline string with user input
    gchar *pipeline_str = g_strdup_printf(
        "filesrc location=%s ! decodebin ! videoconvert ! autovideosink", argv[1]);

    pipeline = gst_parse_launch(pipeline_str, NULL);
    g_free(pipeline_str);

    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_print("Playing video...\n");

    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                     GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    if (msg != NULL) {
        GError *err;
        gchar *debug_info;

        switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_ERROR:
            gst_message_parse_error(msg, &err, &debug_info);
            g_printerr("Error received: %s\n", err->message);
            g_error_free(err);
            g_free(debug_info);
            break;
        case GST_MESSAGE_EOS:
            g_print("End of stream reached.\n");
            break;
        default:
            break;
        }
        gst_message_unref(msg);
    }

    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
