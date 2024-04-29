#include "vga.h"

void vga_text_init(struct vga_text_dev *out) {
    out->mem = (uint16_t*)0xB8000;
    out->dim = (struct vga_text_dim){ .col = 80, .row = 25 };
    out->cursor = (struct vga_text_dim){ .col = 0, .row = 0 };
    out->fgbg = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void vga_clear(struct vga_text_dev *dev) {
    struct vga_text_dim dim = dev->dim;
    uint8_t color = dev->fgbg;
    for (size_t y = 0; y < dim.row; ++y) {
        for (size_t x = 0; x < dim.col; ++x) {
            size_t idx = y * dim.col + x;
            dev->mem[idx] = vga_entry(' ', color);
        }
    }
}

void vga_write(struct vga_text_dev *dev, uint8_t ch) {
    vga_set(dev, ch, dev->cursor);

    // advance cursor
    if (++dev->cursor.col >= dev->dim.col) {
        // go to next line

        // FIXME: Scroll the terminal instead of going OOB
        dev->cursor.col = 0; // Carriage Return
        ++dev->cursor.row;   // Line Feed
    }
}

void vga_set(struct vga_text_dev *dev, uint8_t ch, struct vga_text_dim xy) {
    struct vga_text_dim dim = dev->dim;
    dev->mem[xy.row * dim.col + xy.col] = vga_entry(ch, dev->fgbg);  
}

void vga_set_color(struct vga_text_dev *dev, enum vga_color fg, enum vga_color bg) {
    dev->fgbg = vga_entry_color(fg, bg);
}
