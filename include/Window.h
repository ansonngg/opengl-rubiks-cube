#ifndef WINDOW_N
#define WINDOW_N

class Window {
public:
    Window(int width, int height);
    int Exec();
private:
    const int SCR_WIDTH, SCR_HEIGHT;
};

#endif // WINDOW_N
