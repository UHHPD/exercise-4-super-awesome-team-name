#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>

class Data {
 public:
  Data(const std::string& filename);

  unsigned int size() const { return m_data.size(); }
  double measurement(int i) const { return m_data[i]; }
  double binCenter(int i) const { return 0; }
  double binLow(int i) const { return m_bins.front(); }
  double binHigh(int i) const { return m_bins.back();}
  double error(int i) const { return m_error[i]; }

 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  std::vector<double> m_data;
  std::vector<double> m_error;
  std::vector<double> m_bins;
};

#endif
