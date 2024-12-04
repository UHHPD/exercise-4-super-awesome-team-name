#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
class Data {
 public:
  Data(const std::string& filename);

  unsigned int size() const { return m_data.size(); }
  double measurement(int i) const { return m_data[i]; }
  double binCenter(int i) const { return 0; }
  double binLow(int i) const { return m_bins.front(); }
  double binHigh(int i) const { return m_bins.back();}
  double error(int i) const { return m_error[i]; }
  int checkCompatibility(const Data& in, int n);
 Data operator+( Data& in) {
Data y; 
   if (this->size() != in.size())
   throw std::invalid_argument("Data objects must have the same size for addition.");
   y.m_data.resize(this->size());
   y.m_bins.resize(this->size());
   y.m_error.resize(this->size());
        for (int i = 0; i < this->size(); ++i){
          double w_1 =1/pow(this->error(i),2);
          double w_2 =1/pow(in.error(i),2);
       y.m_data[i] = (this->measurement(i)*(w_1 )+ in.measurement(i)* w_2/(w_1 + w_2));
            y.m_error[i] = sqrt(1/(w_1+w_2));
        }
        return y;
    }

 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  bool compare(Data i, Data j,int bin, int n) const;
  std::vector<double> m_data;
  std::vector<double> m_error;
  std::vector<double> m_bins;
};

#endif
