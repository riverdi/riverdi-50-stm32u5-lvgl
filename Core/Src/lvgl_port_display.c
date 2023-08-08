/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port_display.h"
#include "main.h"
#include "ltdc.h"
#include "dma2d.h"

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void disp_flush (lv_disp_drv_t*, const lv_area_t*, lv_color_t*);
static void disp_flush_complete (DMA2D_HandleTypeDef*);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_disp_drv_t disp_drv;
static lv_disp_draw_buf_t disp_buf;
static __attribute__((aligned(32))) lv_color_t buf_1[MY_DISP_HOR_RES * 64];

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void
lvgl_display_init (void)
{
  /* display initialization */
  ; /* display is already initialized by cubemx-generated code */

  /* display buffer initialization */
  lv_disp_draw_buf_init (&disp_buf,
                         (void*) buf_1,
                         NULL,
                         MY_DISP_HOR_RES * 64);

  /* register the display in LVGL */
  lv_disp_drv_init(&disp_drv);

  /* set the resolution of the display */
  disp_drv.hor_res = MY_DISP_HOR_RES;
  disp_drv.ver_res = MY_DISP_VER_RES;

  /* set callback for display driver */
  disp_drv.flush_cb = disp_flush;
  disp_drv.full_refresh = 0;

  /* interrupt callback for DMA2D transfer */
  hdma2d.XferCpltCallback = disp_flush_complete;

  /* set a display buffer */
  disp_drv.draw_buf = &disp_buf;

  /* finally register the driver */
  lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void
disp_flush (lv_disp_drv_t   *drv,
            const lv_area_t *area,
            lv_color_t      *color_p)
{
  lv_coord_t width = lv_area_get_width(area);
  lv_coord_t height = lv_area_get_height(area);

  //TODO
}

static void
disp_flush_complete (DMA2D_HandleTypeDef *hdma2d)
{
  lv_disp_flush_ready(&disp_drv);
}
