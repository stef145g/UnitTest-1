IF(NOT UNITTEST_LIB_CMAKE)
SET(UNITTEST_LIB_CMAKE 1)

INCLUDE(${GLOBAL_DIR}/Datastructures/CMakeLists.txt)

MESSAGE(STATUS )
MESSAGE(STATUS ========= Unit Test (Lib) ==========)
MESSAGE(STATUS )

SET(CUR_SRC ${GLOBAL_DIR}/UnitTest)
INCLUDE_DIRECTORIES(${GLOBAL_DIR})

SET( SRC_H )
SET( SRC_CPP )
INCLUDE(${CUR_SRC}/Exceptions/CMakeLists.txt)

SET( SRC_H
	${SRC_H}
	${CUR_SRC}/unitTest.h
	${CUR_SRC}/unitTestLog.h
	
	${CUR_SRC}/masterTestHolder.h
	${CUR_SRC}/libraryTests.h
	${CUR_SRC}/testSuite.h

	${CUR_SRC}/singleTest.h
	${CUR_SRC}/singleFunctionTest.h

	${CUR_SRC}/DatastructuresTest.h
)

SET( SRC_CPP
	${SRC_CPP}
	${CUR_SRC}/unitTest.cpp
	
	${CUR_SRC}/masterTestHolder.cpp
	${CUR_SRC}/libraryTests.cpp
	${CUR_SRC}/testSuite.cpp

	${CUR_SRC}/singleTest.cpp
	${CUR_SRC}/singleFunctionTest.cpp
	
	${CUR_SRC}/DatastructuresTest.cpp
)

ADD_LIBRARY( UnitTestLib STATIC
	${SRC_CPP}
	${SRC_H}
)
SET( TEST_INIT ${CUR_SRC}/UnitTestExe/defaultTestInit.cpp )

ENDIF(NOT UNITTEST_LIB_CMAKE)