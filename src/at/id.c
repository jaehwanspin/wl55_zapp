#include "./id.h"
#include "../app.h"
#include "../device/devices.h"
#include "../telemetry/uart_io.h"
#include "../util/arg_parse.h"

#include "../util/custom_typedefs.h"

#include <lorawan/lorawan.h>

#include <string.h>

static struct arg_parse_option opts[] = {
    { { "DevAddr" }, bbnb_both, ARG_PARSE_VALUE_TYPE_STRING },
    { { "DevEui" }, bbnb_both, ARG_PARSE_VALUE_TYPE_STRING },
    { { "AppEui" }, bbnb_both, ARG_PARSE_VALUE_TYPE_STRING }
};
static struct arg_parse_context ap_ctx =
    { opts, sizeof(opts) / sizeof(struct arg_parse_option) };

// from src/main.c
extern struct app_data app_data;
static struct device* uart = nullptr;


/**
 * @author Jin
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int at_id_handler(int argc, char** argv)
{
    int res = 0;
    bbn_bool parsed_res = bbnb_not_found;
    struct arg_parse_result parsed_val = { 0, };

    uart = (struct device*)app_data.devs->uart;

    if (argc > 2)
    {
        parsed_res = arg_parse_set_args(&ap_ctx, argc, argv, &parsed_val);

        switch (parsed_res)
        {
        case bbnb_found:
        {
            char trim_val[256] = { 0, };
 
            app_data.lorawan_cfg->otaa.

            if (0 == strcmp("DevAddr", parsed_val.value.string_value))
            {
                
            }
            else if (0 == strcmp("DevEui", parsed_val.value.string_value))
            {

            }
            else if (0 == strcmp("AppEui", parsed_val.value.stri`ng_value))
            {
                
            }
            break;
        }
        case bbnb_found_but_not_has_value:
        {
            str8_32_t out_val = { 0, };

            if (0 == strcmp("DevAddr", parsed_val.value.string_value))
            {
                
            }
            else if (0 == strcmp("DevEui", parsed_val.value.string_value))
            {

            }
            else if (0 == strcmp("AppEui", parsed_val.value.string_value))
            {
                
            }
            break;
        }
        case bbnb_not_found:
        {
            
            break;
        }
        case bbnb_error:
        {
            break;
        }
        }
    }
    else // AT+ID
    {

    }
   
    return res;
}