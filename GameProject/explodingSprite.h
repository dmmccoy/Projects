#include <vector>
#include <list>
#include "chunk.h"

class ExplodingSprite : public Sprite {
public:
  ExplodingSprite(const Sprite& s);
  ExplodingSprite(const std::string& name, const int& x, const int& y);
  ExplodingSprite(const ExplodingSprite&); // Explicit disallow (Item 6)
  ~ExplodingSprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void makeChunks(unsigned int);
  inline float getScale()const{ return scale; }
  void  setScale(float s){ scale = s; }
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
private:
  std::list<Chunk*> chunks; // An ExplodingSprite is a list of sprite chunks
  std::list<Chunk*> freeList; // When a chunk gets out of range it goes here
  float scale;

  ExplodingSprite& operator=(const ExplodingSprite&); // (Item 6)
};
