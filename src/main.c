#include "./app.h"

void main(void)
{
    struct app_data app_data = { 0, };
    app_init(&app_data);
    app_start(&app_data);
}
