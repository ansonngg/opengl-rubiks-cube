#include "Painter.h"

#include <glm/gtc/matrix_transform.hpp>

Painter::Painter(int width, int height)
    : SCR_WIDTH(width)
    , SCR_HEIGHT(height)
    , eye(-5.0f, 5.0f, 10.0f)
    , center(0.0f, 0.0f, 0.0f)
    , rubiksCube(0.2f) {}

void Painter::Initialize() {
    shader.Setup("../shader/VertexShader.glsl", "../shader/FragmentShader.glsl");
    rubiksCube.Initialize();
}

void Painter::Loop() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.Use();

    glm::mat4 viewMatrix = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 vpMatrix = projectionMatrix * viewMatrix;

    ProcessInput();
    rubiksCube.Paint(shader, vpMatrix);
}

void Painter::ProcessInput() {
    if (keyboardCtrl.x) {
        if (rubiksCube.RotateCube(RubiksCube::Rotate::X)) {
            keyboardCtrl.x = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.y) {
        if (rubiksCube.RotateCube(RubiksCube::Rotate::Y)) {
            keyboardCtrl.y = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.z) {
        if (rubiksCube.RotateCube(RubiksCube::Rotate::Z)) {
            keyboardCtrl.z = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.xp) {
        if (rubiksCube.RotateCube(RubiksCube::Rotate::XP)) {
            keyboardCtrl.xp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.yp) {
        if (rubiksCube.RotateCube(RubiksCube::Rotate::YP)) {
            keyboardCtrl.yp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.zp) {
        if (rubiksCube.RotateCube(RubiksCube::Rotate::ZP)) {
            keyboardCtrl.zp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.f) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::F)) {
            keyboardCtrl.f = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.b) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::B)) {
            keyboardCtrl.b = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.u) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::U)) {
            keyboardCtrl.u = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.d) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::D)) {
            keyboardCtrl.d = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.l) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::L)) {
            keyboardCtrl.l = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.r) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::R)) {
            keyboardCtrl.r = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.m) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::M)) {
            keyboardCtrl.m = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.e) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::E)) {
            keyboardCtrl.e = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.s) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::S)) {
            keyboardCtrl.s = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.f2) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::F2)) {
            keyboardCtrl.f2 = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.b2) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::B2)) {
            keyboardCtrl.b2 = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.u2) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::U2)) {
            keyboardCtrl.u2 = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.d2) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::D2)) {
            keyboardCtrl.d2 = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.l2) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::L2)) {
            keyboardCtrl.l2 = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.r2) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::R2)) {
            keyboardCtrl.r2 = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.fp) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::FP)) {
            keyboardCtrl.fp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.bp) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::BP)) {
            keyboardCtrl.bp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.up) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::UP)) {
            keyboardCtrl.up = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.dp) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::DP)) {
            keyboardCtrl.dp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.lp) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::LP)) {
            keyboardCtrl.lp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.rp) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::RP)) {
            keyboardCtrl.rp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.mp) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::MP)) {
            keyboardCtrl.mp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.ep) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::EP)) {
            keyboardCtrl.ep = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.sp) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::SP)) {
            keyboardCtrl.sp = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.f2p) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::F2P)) {
            keyboardCtrl.f2p = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.b2p) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::B2P)) {
            keyboardCtrl.b2p = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.u2p) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::U2P)) {
            keyboardCtrl.u2p = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.d2p) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::D2P)) {
            keyboardCtrl.d2p = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.l2p) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::L2P)) {
            keyboardCtrl.l2p = false;
            keyboardCtrl.acceptInput = true;
        }
    } else if (keyboardCtrl.r2p) {
        if (rubiksCube.MoveLayer(RubiksCube::Move::R2P)) {
            keyboardCtrl.r2p = false;
            keyboardCtrl.acceptInput = true;
        }
    }
}
