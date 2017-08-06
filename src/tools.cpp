#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

static const double TWO_PI = 2. * M_PI;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {

  VectorXd rmse(4);
  rmse << 0.0f,0.0f,0.0f,0.0f;

  // check the validity of the following inputs:
  //  * the estimation vector size should not be zero
  //  * the estimation vector size should equal ground truth vector size
  if(estimations.size() != ground_truth.size() || estimations.size() == 0){
      cout << "Invalid estimation or ground_truth data" << endl;
      return rmse;
  }

  //accumulate squared residuals
  for(unsigned int i=0; i < estimations.size(); ++i){
      VectorXd residual = estimations[i] - ground_truth[i];
      residual = residual.array()*residual.array(); //coefficient-wise multiplication
      rmse += residual;
  }

  rmse = rmse/estimations.size(); //calculate the mean
  rmse = rmse.array().sqrt(); //calculate the squared root
  return rmse;

}

double Tools::normalizeAngle(double angle) {
    while (angle > M_PI) angle -= TWO_PI;
    while (angle < -M_PI) angle += TWO_PI;
    return angle;
};
