#include <pebble.h>

#include "myroll.h"

static Window *window;
static TextLayer *text_layer;
static GBitmap* gbitmap_heads;
static GBitmap* gbitmap_revs;
static BitmapLayer *bitmaplayer_icon;
static char s[20];


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  
  //snprintf(s, sizeof(s), "Down %d", my_roll_int(1, 2));
  
  int result = my_roll_int(1, 2);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Down %d", result);
  
  if(result==1)
    bitmap_layer_set_bitmap(bitmaplayer_icon, gbitmap_heads);
  else
     bitmap_layer_set_bitmap(bitmaplayer_icon, gbitmap_revs);
  //text_layer_set_text(text_layer,s);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(text_layer, "Press down button to start!");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
 
  
  
  gbitmap_heads = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COIN_HEADS);
  gbitmap_revs  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COIN_REVE);
  
  bitmaplayer_icon = bitmap_layer_create(GRect(2,14,140,140));
  bitmap_layer_set_background_color(bitmaplayer_icon, GColorClear);
  bitmap_layer_set_compositing_mode(bitmaplayer_icon, GCompOpSet);
  
   layer_add_child(window_layer, text_layer_get_layer(text_layer));
   layer_add_child(window_layer, bitmap_layer_get_layer(bitmaplayer_icon));
}

static void window_unload(Window *window) {
  
    gbitmap_destroy(gbitmap_heads);
   gbitmap_destroy(gbitmap_revs);
  bitmap_layer_destroy(bitmaplayer_icon);
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}