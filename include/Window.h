#ifndef WINDOW_N
#define WINDOW_N

class Window {
public:
    Window(int width, int height, int sampleNum = 1);
    int Exec();
private:
    const int SCR_WIDTH, SCR_HEIGHT, SAMPLE_NUM;
};

#endif // WINDOW_N
