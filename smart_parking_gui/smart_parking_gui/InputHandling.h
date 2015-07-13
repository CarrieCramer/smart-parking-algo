#ifndef __InputHandling__
#define __InputHandling__
// An h file designed to catch exceptions in the CLI
class InvalidInput {
 public:
  InvalidInput (char * in_ptr): msg_ptr(in_ptr) { }
  const char * const msg_ptr;
 
 private:
  InvalidInput(); // no default constructions
};

#endif
