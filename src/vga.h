#include <stdint.h>
#include <stddef.h>

struct vga_text_dim {
    size_t col;
    size_t row;
};

// TODO: Split vga_text_dev into vga_text_dev and vga_serial_dev.
// vga_text_dev should not include a cursor, or color information.
struct vga_text_dev {
    uint16_t *mem;
    struct vga_text_dim dim;
    struct vga_text_dim cursor;
    uint8_t fgbg;
};

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

void vga_text_init(struct vga_text_dev *dev);
void vga_clear(struct vga_text_dev *dev);
void vga_write(struct vga_text_dev *dev, uint8_t ch);
void vga_set(struct vga_text_dev *dev, uint8_t ch, struct vga_text_dim xy);
void vga_set_color(struct vga_text_dev *dev, enum vga_color fg, enum vga_color bg);

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(uint8_t ch, uint8_t color) {
	return (uint16_t) ch | (uint16_t) color << 8;
}
