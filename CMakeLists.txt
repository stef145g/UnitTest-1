IF(NOT UNITTEST_LIB_CMAKE)
SET(UNITTEST_LIB_CMAKE 1)

INCLUDE(${GLOBAL_DIR}/Datastructures/CMakeLists.txt)

MESSAGE(STATUS )
MESSAGE(STATUS ========= Unit Test (Lib) ==========)
MESSAGE(STATUS )

SET(CUR_SRC ${GLOBAL_DIR}/UnitTest)
INCLUDE_DIRECTORIES(${CUR_SRC})

SET( SRC_H
	${CUR_SRC}/UnitTest.h
	${CUR_SRC}/UnitTestLog.h
	${CUR_SRC}/masterTestHolder.h
	${CUR_SRC}/UnitTestExceptions.h
	${CUR_SRC}/DatastructuresTest.h
	${CUR_SRC}/TestSuite.h
	${CUR_SRC}/singleTest.h
)

SET( SRC_CPP
	${CUR_SRC}/UnitTest.cpp
	${CUR_SRC}/masterTestHolder.cpp
	${CUR_SRC}/DatastructuresTest.cpp
	${CUR_SRC}/TestSuite.cpp
	${CUR_SRC}/singleTest.cpp
)

ADD_LIBRARY( UnitTestLib STATIC
	${SRC_CPP}
	${SRC_H}
)
SET( TEST_INIT ${CUR_SRC}/UnitTestExe/defaultTestInit.cpp )

ENDIF(NOT UNITTEST_LIB_CMAKE)