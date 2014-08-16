#ifndef THREE_EXAMPLES_UTILS_IMPROVED_NOISE
#define THREE_EXAMPLES_UTILS_IMPROVED_NOISE

#include <three/examples/utils/improved_noise.h>

namespace three {

float ImprovedNoise::noise(float x, float y, float z) const {

  int floorX = (int)x, floorY = (int)y, floorZ = (int)z;

  float X = (float)(floorX & 255), Y = (float)(floorY & 255), Z = (float)(floorZ & 255);

  x -= (float)floorX;
  y -= (float)floorY;
  z -= (float)floorZ;

  float xMinus1 = x -1, yMinus1 = y - 1, zMinus1 = z - 1;

  float u = fade(x), v = fade(y), w = fade(z);

  float A = p[X]+Y, AA = p[A]+Z, AB = p[A+1]+Z, B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;

  return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
          grad(p[BA], xMinus1, y, z)),
        lerp(u, grad(p[AB], x, yMinus1, z),
          grad(p[BB], xMinus1, yMinus1, z))),
      lerp(v, lerp(u, grad(p[AA+1], x, y, zMinus1),
          grad(p[BA+1], xMinus1, y, z-1)),
        lerp(u, grad(p[AB+1], x, yMinus1, zMinus1),
          grad(p[BB+1], xMinus1, yMinus1, zMinus1))));

}

float ImprovedNoise::fade( float t ) const {
  return t * t * t * (t * (t * 6.f - 15.f) + 10.f);
}

float ImprovedNoise::lerp( float t, float a, float b ) const {
  return a + t * (b - a);
}

float ImprovedNoise::grad( unsigned char hash, int x, int y, int z ) const {
  auto h = hash & 15;
  auto u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
  return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

ImprovedNoise::ImprovedNoise() {}

}

#endif // THREE_EXAMPLES_UTILS_IMPROVED_NOISE
