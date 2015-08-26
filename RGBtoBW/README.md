#### RGB to BW

人眼吸收綠色比其他顏色敏感，所以當影像變成灰階時，僅僅將紅色、綠色、藍色加總取平均，這是不夠的，常見的方法是將 red * 77, green * 151, blue * 28，這三個除數的總和為 256，可使除法變簡單。

給定每個 pixel 為 32-bit 的 RGBA (A = alpha, 透明度) 的 bitmap，其轉換為黑白影像的函式為：

    void rgba_to_bw(uint32_t *bitmap, int width, int height, long stride) {
        int row, col;
        uint32_t pixel, r, g, b, a, bw;
        for (row = 0; row < height; row++) {
            for (col = 0; col < width; col++) {
                pixel = bitmap[col + row + stride / 4];
                a = (pixel >> 24) & 0xff;
                r = (pixel >> 16) & 0xff;
                g = (pixel >> 8) & 0xff;
                b = pixel & 0xff;
                bw = (uint32_t) (r * 0.299 + g * 0.587 + b * 0.114);
                bitmap[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
            }
        }
    }

請提出效能改善的方案：
1.建立表格加速浮點數操作 (L1 cache?)
2.減少位移數量
3.最終輸出的緩衝區 (in-place)

Hint: 如果先計算針對「乘上 0.299」一類的運算，先行計算後建立表格呢？