#include "../controller/controller.cc"
#include "../model/3d_model.cc"
#include "gtest/gtest.h"

using s21::ViewerController;
using s21::ViewerModel;
using s21::ViewerSettings;

class ViewerTest : public ::testing::Test {
 protected:
  void SetUp() { test_controller->Parse3DModel("Objects/test1.obj"); }
  double eps = 10E-3;
  void TearDown() {}
  ViewerModel* test_model = ViewerModel::GetInstance();
  ViewerController* test_controller = ViewerController::GetInstance(test_model);
};

TEST_F(ViewerTest, GetIsModelLoaded) {
  bool my = test_controller->GetIsModelLoaded();
  EXPECT_EQ(my, true);
}

TEST_F(ViewerTest, GetScale) {
  double my = test_controller->GetScale();
  EXPECT_EQ(my, 0);
}

TEST_F(ViewerTest, GetRecordStatus) {
  bool my = test_controller->GetRecordStatus();
  EXPECT_EQ(my, false);
}

TEST_F(ViewerTest, GetCountOfFrames) {
  unsigned int my = test_controller->GetCountOfFrames();
  EXPECT_EQ(my, 0u);
}

TEST_F(ViewerTest, GetFrustum) {
  double my = test_controller->GetFrustum();
  EXPECT_NEAR(my, 2.2391, eps);
}

TEST_F(ViewerTest, GetHeapHeight) {
  double my = test_controller->GetHeapHeight();
  EXPECT_NEAR(my, 258.549, eps);
}

TEST_F(ViewerTest, GetLeft) {
  double my = test_controller->GetLeft();
  EXPECT_NEAR(my, -58.3591, eps);
}

TEST_F(ViewerTest, GetRight) {
  double my = test_controller->GetRight();
  EXPECT_NEAR(my, 187.942, eps);
}

TEST_F(ViewerTest, GetTop) {
  double my = test_controller->GetTop();
  EXPECT_NEAR(my, 235.106, eps);
}

TEST_F(ViewerTest, GetBottom) {
  double my = test_controller->GetBottom();
  EXPECT_NEAR(my, -11.1955, eps);
}

TEST_F(ViewerTest, GetFar) {
  double my = test_controller->GetFar();
  EXPECT_NEAR(my, 330.441, eps);
}

TEST_F(ViewerTest, GetNear) {
  double my = test_controller->GetNear();
  EXPECT_NEAR(my, -312.809, eps);
}

TEST_F(ViewerTest, GetCountOfFacets) {
  unsigned int my = test_controller->GetCountOfFacets();
  EXPECT_EQ(my, 664u);
}

TEST_F(ViewerTest, GetCountOfVertices) {
  unsigned int my = test_controller->GetCountOfVertices();
  EXPECT_EQ(my, 666u);
}

TEST_F(ViewerTest, GetNumbersOfVerticesInFacet) {
  unsigned int my = test_controller->GetNumbersOfVerticesInFacet(5);
  EXPECT_EQ(my, 4u);
}

TEST_F(ViewerTest, GetConcretePolygonVertices) {
  unsigned int* my = test_controller->GetConcretePolygonVertices(4);
  EXPECT_EQ(my[0], 6u);
  EXPECT_EQ(my[1], 1u);
  EXPECT_EQ(my[2], 1u);
  EXPECT_EQ(my[3], 0u);
}

TEST_F(ViewerTest, GetVertices) {
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], -8.131, eps);
  EXPECT_NEAR(my[1], 151.712, eps);
  EXPECT_NEAR(my[2], 97.014, eps);
  EXPECT_NEAR(my[3], -5.8495, eps);
}

TEST_F(ViewerTest, SetXAngle) {
  test_controller->SetXAngle(90);
  test_controller->UpdateVertices();
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], -8.131, eps);
  EXPECT_NEAR(my[1], -97.014, eps);
  EXPECT_NEAR(my[2], 151.711, eps);
  EXPECT_NEAR(my[3], -5.8495, eps);
}

TEST_F(ViewerTest, SetYAngle) {
  test_controller->SetYAngle(-90);
  test_controller->UpdateVertices();
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], -151.712, eps);
  EXPECT_NEAR(my[1], -97.014, eps);
  EXPECT_NEAR(my[2], -8.131, eps);
  EXPECT_NEAR(my[3], -151.9693, eps);
}

TEST_F(ViewerTest, SetZAngle) {
  test_controller->SetZAngle(180);
  test_controller->UpdateVertices();
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], 151.7116, eps);
  EXPECT_NEAR(my[1], 97.014, eps);
  EXPECT_NEAR(my[2], -8.131, eps);
  EXPECT_NEAR(my[3], 151.9693, eps);
}

TEST_F(ViewerTest, SetXShift) {
  test_controller->SetXShift(34);
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], 151.7116, eps);
  EXPECT_NEAR(my[1], 97.014, eps);
  EXPECT_NEAR(my[2], -8.131, eps);
  EXPECT_NEAR(my[3], 151.9693, eps);
}

TEST_F(ViewerTest, SetYShift) {
  test_controller->SetYShift(100);
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], 227.841, eps);
  EXPECT_NEAR(my[1], 97.014, eps);
  EXPECT_NEAR(my[2], -8.131, eps);
  EXPECT_NEAR(my[3], 228.0987, eps);
}

TEST_F(ViewerTest, SetZShift) {
  test_controller->SetZShift(-100);
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], 227.841, eps);
  EXPECT_NEAR(my[1], 320.9239, eps);
  EXPECT_NEAR(my[2], -8.131, eps);
  EXPECT_NEAR(my[3], 228.0987, eps);
}

TEST_F(ViewerTest, SetScale) {
  test_controller->SetScale(1.5);
  double* my = test_controller->GetVertices();
  EXPECT_NEAR(my[0], 227.841, eps);
  EXPECT_NEAR(my[1], 320.924, eps);
  EXPECT_NEAR(my[2], -455.951, eps);
  EXPECT_NEAR(my[3], 228.099, eps);
}

TEST_F(ViewerTest, SetRecordStatus) {
  test_controller->SetRecordStatus(true);
  bool my = test_controller->GetRecordStatus();
  EXPECT_EQ(my, true);
}

TEST_F(ViewerTest, SetCountOfFrames) {
  test_controller->SetCountOfFrames(6);
  unsigned int my = test_controller->GetCountOfFrames();
  EXPECT_EQ(my, 6u);
}

TEST_F(ViewerTest, GetLineWidth) {
  unsigned int my = test_controller->GetLineWidth();
  EXPECT_EQ(my, 1u);
}

TEST_F(ViewerTest, GetVertexWidth) {
  unsigned int my = test_controller->GetVertexWidth();
  EXPECT_EQ(my, 1u);
}

TEST_F(ViewerTest, GetIsLineDotted) {
  bool my = test_controller->GetIsLineDotted();
  EXPECT_EQ(my, false);
}

TEST_F(ViewerTest, GetIsProjectionCentral) {
  bool my = test_controller->GetIsProjectionCentral();
  EXPECT_EQ(my, false);
}

TEST_F(ViewerTest, GetIsVertexRound) {
  bool my = test_controller->GetIsVertexRound();
  EXPECT_EQ(my, false);
}

TEST_F(ViewerTest, GetColorBackgroundRed) {
  float my = test_controller->GetColorBackgroundRed();
  EXPECT_EQ(my, 255.0f);
}

TEST_F(ViewerTest, GetColorBackgroundGreen) {
  float my = test_controller->GetColorBackgroundGreen();
  EXPECT_EQ(my, 255.0f);
}

TEST_F(ViewerTest, GetColorBackgroundBlue) {
  float my = test_controller->GetColorBackgroundBlue();
  EXPECT_EQ(my, 255.0f);
}

TEST_F(ViewerTest, GetColorLineRed) {
  float my = test_controller->GetColorLineRed();
  EXPECT_EQ(my, 0);
}

TEST_F(ViewerTest, GetColorLineGreen) {
  float my = test_controller->GetColorLineGreen();
  EXPECT_EQ(my, 0);
}

TEST_F(ViewerTest, GetColorLineBlue) {
  float my = test_controller->GetColorLineBlue();
  EXPECT_EQ(my, 0);
}

TEST_F(ViewerTest, GetColorVertexRed) {
  float my = test_controller->GetColorVertexRed();
  EXPECT_EQ(my, 255.0f);
}

TEST_F(ViewerTest, GetColorVertexGreen) {
  float my = test_controller->GetColorVertexGreen();
  EXPECT_EQ(my, 0);
}

TEST_F(ViewerTest, GetColorVertexBlue) {
  float my = test_controller->GetColorVertexBlue();
  EXPECT_EQ(my, 0);
}

TEST_F(ViewerTest, SetLineWidth) {
  test_controller->SetLineWidth(6);
  unsigned int my = test_controller->GetLineWidth();
  EXPECT_EQ(my, 6u);
}

TEST_F(ViewerTest, SetVertexWidth) {
  test_controller->SetVertexWidth(10);
  unsigned int my = test_controller->GetVertexWidth();
  EXPECT_EQ(my, 10u);
}

TEST_F(ViewerTest, SetIsLineDotted) {
  test_controller->SetIsLineDotted(true);
  bool my = test_controller->GetIsLineDotted();
  EXPECT_EQ(my, true);
}

TEST_F(ViewerTest, SetIsProjectionCentral) {
  test_controller->SetIsProjectionCentral(true);
  bool my = test_controller->GetIsProjectionCentral();
  EXPECT_EQ(my, true);
}

TEST_F(ViewerTest, SetIsVertexRound) {
  test_controller->SetIsVertexRound(true);
  bool my = test_controller->GetIsVertexRound();
  EXPECT_EQ(my, true);
}

TEST_F(ViewerTest, SetColorBackgroundRed) {
  test_controller->SetColorBackgroundRed(100.0f);
  float my = test_controller->GetColorBackgroundRed();
  EXPECT_EQ(my, 100.0f);
}

TEST_F(ViewerTest, SetColorBackgroundGreen) {
  test_controller->SetColorBackgroundGreen(5.0f);
  float my = test_controller->GetColorBackgroundGreen();
  EXPECT_EQ(my, 5.0f);
}

TEST_F(ViewerTest, SetColorBackgroundBlue) {
  test_controller->SetColorBackgroundBlue(255.0f);
  float my = test_controller->GetColorBackgroundBlue();
  EXPECT_EQ(my, 255.0f);
}

TEST_F(ViewerTest, SetColorLineRed) {
  test_controller->SetColorLineRed(144.0f);
  float my = test_controller->GetColorLineRed();
  EXPECT_EQ(my, 144.0f);
}

TEST_F(ViewerTest, SetColorLineGreen) {
  test_controller->SetColorLineGreen(8.0f);
  float my = test_controller->GetColorLineGreen();
  EXPECT_EQ(my, 8.0f);
}

TEST_F(ViewerTest, SetColorLineBlue) {
  test_controller->SetColorLineBlue(3.44f);
  float my = test_controller->GetColorLineBlue();
  EXPECT_EQ(my, 3.44f);
}

TEST_F(ViewerTest, SetColorVertexRed) {
  test_controller->SetColorVertexRed(50.0f);
  float my = test_controller->GetColorVertexRed();
  EXPECT_EQ(my, 50.0f);
}

TEST_F(ViewerTest, SetColorVertexGreen) {
  test_controller->SetColorVertexGreen(30.0f);
  float my = test_controller->GetColorVertexGreen();
  EXPECT_EQ(my, 30.0f);
}

TEST_F(ViewerTest, SetColorVertexBlue) {
  test_controller->SetColorVertexBlue(200.01f);
  float my = test_controller->GetColorVertexBlue();
  EXPECT_EQ(my, 200.01f);
}

int main(int argc, char** argv) {
  setenv("LC_NUMERIC", "C", 1);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
