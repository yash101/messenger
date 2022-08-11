#include "messenger/message.h"

#ifdef __cplusplus

MessengerMessage::MessengerMessage() :
  buffered_in(0),
  buffered_out(0)
{
}

MessengerMessage::~MessengerMessage()
{
}

std::vector<char>
MessengerMessage::read()
{
  std::vector<char> ret;
  ret.reserve(buffered_in);
  for (auto it = incoming.begin(); it != incoming.end(); ++it)
  {
    buffered_in -= it->size();
    ret.insert(ret.end(), it->begin(), it->end());
  }

  incoming.clear();

  return ret;
}

std::vector<char>
MessengerMessage::read(
  size_t num
)
{
  size_t remaining = num;
  std::vector<char> ret;
  ret.reserve(num);

  try
  {
    while (remaining > 0 && !incoming.empty())
    {
      auto& cur = incoming.front();
      if (cur.size() < remaining)
      {
        ret.insert(ret.end(), cur.begin(), cur.end());
        remaining -= cur.size();
        incoming.pop_front();
      }
      else
      {
        ret.insert(ret.end(), cur.begin(), cur.begin() + remaining);
        cur.erase(cur.begin(), cur.begin() + remaining);
        remaining -= cur.size();
      }
    }
  }
  catch(std::exception& e) { }

  return ret;
}

std::vector<char>
MessengerMessage::readSingleBuffer()
{
  auto vec = incoming.front();
  incoming.pop_front();
  return vec;
}

size_t
MessengerMessage::read(
  char* buffer,
  size_t maxlen
)
{
  if (!buffer)
    return 0;

  char* iterator = buffer;

  size_t length = 0;
  while (length < maxlen)
  {
    auto& cur = incoming.front();
    if (cur.size() < maxlen - length)
    {
      iterator = std::copy(cur.begin(), cur.end(), iterator);
      length += cur.size();
    }
    else
    {
      iterator = std::copy(cur.begin(), cur.begin() + maxlen - length, iterator);
      length = maxlen - length;
    }
    incoming.pop_front();
  }

  buffered_in -= length;
  return length;
}

std::vector<char>
MessengerMessage::peek()
{
  return std::vector<char>{};
}

std::vector<char>
MessengerMessage::peek(
  size_t num
)
{
  return std::vector<char>{};
}

std::vector<char>
MessengerMessage::peekSingleBuffer()
{
  return incoming.empty() ?
    std::vector<char>{} :
    incoming.front();
}

// Need to implement
std::vector<char> MessengerMessage::readUntil(
  std::vector<char> ending
)
{
  // size_t ehash = 0;
  // size_t rhash = 0;

  // if (ending.size() > buffered_in)
  //   return std::vector<char>{};

  // for (auto it = ending.begin(); it != ending.end(); ++it)
  //   ehash += *it;
  
  // size_t wsize = ending.size();

  // size_t char_iterator = 0;
  // decltype(incoming)::iterator wstartit = incoming.begin();
  // decltype(incoming)::iterator wendit = incoming.begin();

  // char last = 

  // while (char_iterator < buffered_in)
  // {
  //   auto& buffer = *wendit;
  //   size_t i = 0;
  //   while (char_iterator < buffered_in && i++ < buffer.size())
  //   {
  //   }
  // }

  return std::vector<char>{};
}

size_t
MessengerMessage::readUntil(
  char* buffer,
  size_t maxlen,
  const char* ending,
  size_t elength
)
{
  return 0;
}

#endif
