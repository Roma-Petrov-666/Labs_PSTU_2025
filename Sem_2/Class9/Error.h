#pragma once

#include <string>
#include <iostream>

class Error {
public:
    virtual void what() const = 0;
};

class IndexError : public Error {
protected:
    std::string msg;
public:
    IndexError() : msg("Index Error\n") {}
    virtual void what() const override { std::cout << msg; }
};

class IndexErrorNegative : public IndexError {
public:
    IndexErrorNegative() : IndexError() { msg = "index < 0\n"; }
    void what() const override { std::cout << msg; }
};

class IndexErrorLarge : public IndexError {
public:
    IndexErrorLarge() : IndexError() { msg = "index >= size\n"; }
    void what() const override { std::cout << msg; }
};

class SizeError : public Error {
protected:
    std::string msg;
public:
    SizeError() : msg("size error\n") {}
    virtual void what() const override { std::cout << msg; }
};

class MaxSizeError : public SizeError {
public:
    MaxSizeError() : SizeError() { msg = "size > MAX_SIZE\n"; }
    void what() const override { std::cout << msg; }
};

class OverflowError : public SizeError {
public:
    OverflowError() : SizeError() { msg = "set overflow (++)\n"; }
    void what() const override { std::cout << msg; }
};

class UnionOverflowError : public SizeError {
public:
    UnionOverflowError() : SizeError() { msg = "union result too large\n"; }
    void what() const override { std::cout << msg; }
};