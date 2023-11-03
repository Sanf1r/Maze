#ifndef DATA_H
#define DATA_H

#include <vector>

class Data {
 public:
  Data() = default;
  int& operator()(int row, int columns) {
    return data_[row * columns_ + columns];
  }

  void Clear() { data_.clear(); }

  void Push(int num) { data_.push_back(num); }

  void SetCol(int num) { columns_ = num; }

  void SetRows(int newRows) { rows_ = newRows; }

  int GetRows() const { return rows_; }

  int GetColumns() const { return columns_; }

  void Init(int size, int num) {
      data_.resize(size,num);
      std::fill(data_.begin(), data_.end(), num);
  }

 private:
  int rows_ = 0;
  int columns_= 0;
  std::vector<int> data_;
};

#endif  // DATA_H
