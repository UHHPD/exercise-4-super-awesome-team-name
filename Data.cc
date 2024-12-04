#include "Data.hh"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include <cmath>

using namespace std;


double f_x(double x){
  double alpha = 0.005;
  double beta = -0.00001;
  double gamma = 0.08;
  double delta = 0.015;

  return alpha + beta * x + gamma * exp(-delta*x);
}

// take two data points and compare their difference with the error
bool Data::compare(Data i, Data j,int bin, int n) const {
  double diff = i.m_data[bin] - j.m_data[bin];
    if (diff ==0) return true;
  double error =  sqrt(pow((i.m_data[bin] - j.m_data[bin])/(abs(diff))* i.m_error[bin],2) + pow((j.m_data[bin] - i.m_data[bin])/(abs(diff))* j.m_error[bin],2));
  return abs(diff) < n*error;
}
Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
    // read in data from file: error 
    for (int i = 0; i < size; ++i) {
      double error;
      file >> error;
      m_error.push_back(error);
    }
m_name = filename;

  // done! close the file
  file.close();

  assertSizes();
};
// check if two data sets are within n errors of each other and return the number that are not
int Data::checkCompatibility(const Data& in, int n) {
    int count = 0;
    for (int i = 0; i < m_data.size(); ++i) {
        if (!compare(*this,in,i, n)) {
        count++;
        }
    }
    return count;


}
void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size()); }
Data Data::operator+(Data& in){
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

double Data::chi_2(){
  double sum = 0;
  for (int i = 0; i < this->size(); ++i){
    sum += pow(this->measurement(i) - f_x(this->binCenter(i)),2)/pow(this->error(i),2);
  }
  return sum/56;
}
