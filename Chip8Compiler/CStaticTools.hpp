#ifndef CSTATICTOOLS_HPP
#define CSTATICTOOLS_HPP

// SAFE_DELETE-Makro
#define SAFE_DELETE(X) {if(X!=nullptr) {delete(X); X=nullptr;}}

#endif