#include "../logging.h"

void my_function() {
    LOG_ERROR("Message without arguments logged.");
    LOG_ERROR("Message with one argument (%f) logged.", 2.0f);
    LOG_ERROR("Message with two arguments (%f, %.1f) logged.", 2.3f, 3.45f);
    
    LOG_INFO("Info message logged.");
    LOG_DEBUG("Debug message logged.");
}

int main ( int argc, char **argv )
{
    my_function();
    
    LOG_ERROR("Message from main function logged.");
    
    return 0;
}