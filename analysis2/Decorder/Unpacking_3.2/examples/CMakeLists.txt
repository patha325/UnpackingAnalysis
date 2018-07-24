message(STATUS "examples ... ")

ADD_EXECUTABLE(dump         babyMindDataDump.cpp)
TARGET_LINK_LIBRARIES(dump  BabyMINDUnpack)

if    (ROOT_FOUND)
  ADD_EXECUTABLE(unpack                     babyMindUnpack.cpp)
  TARGET_LINK_LIBRARIES(unpack              BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(ufe-monitor                ufe_monitor.cpp)
  TARGET_LINK_LIBRARIES(ufe-monitor         BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(RootFileAnalyssis          t9rootFileanalysis.cpp)
  TARGET_LINK_LIBRARIES(RootFileAnalyssis   BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(TDMunpack                  babyMINDTDMUnpack.cpp)
  TARGET_LINK_LIBRARIES(TDMunpack           BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(NewAnalysis                new_analysis.cpp)
  TARGET_LINK_LIBRARIES(NewAnalysis         BabyMINDUnpack ${ROOT_LIBRARIES})
  
  #ADD_EXECUTABLE(Calibration                babyMindCalibration.cpp)
  #TARGET_LINK_LIBRARIES(Calibration         BabyMINDUnpack "${ROOT_LIBRARIES} -lSpectrum")

  ADD_EXECUTABLE(GTrigTagSearch             GTrigTagSearch.cpp)
  TARGET_LINK_LIBRARIES(GTrigTagSearch      BabyMINDUnpack ${ROOT_LIBRARIES})
  
  ADD_EXECUTABLE(HG_vs_LG_calib             HG_LG_calib.cpp)
  TARGET_LINK_LIBRARIES(HG_vs_LG_calib      BabyMINDUnpack ${ROOT_LIBRARIES})
  
  ADD_EXECUTABLE(LG_vs_ToT_calib             LG_vs_ToT_calib.cpp)
  TARGET_LINK_LIBRARIES(LG_vs_ToT_calib      BabyMINDUnpack ${ROOT_LIBRARIES})
  
endif (ROOT_FOUND)
