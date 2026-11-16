// 격자, 풀 재생
#pragma once

const int WIDTH = 20;       // 격자 기로 칸 수
const int HEIGHT = 16;      // 격자 세로 칸 수
const int GRASS_START = 50; // 처음에 풀이 있을 확률(%)
const int GRASS_REGROW = 4;  // 풀이 없는 칸에 매 턴 풀이 다시 날 확률(%)

// 토끼
const int RABBIT_COUNT = 15;    // 처음 토끼 수
const int RABBIT_ENERGY = 6;    // 토끼 시작 에너지
const int RABBIT_EAT = 4;       // 풀을 먹으면 얻는 에너지