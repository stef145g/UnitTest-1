IF(NOT UNITTEST_LIB_EXCEPTIONS_CMAKE)
SET(UNITTEST_LIB_EXCEPTIONS_CMAKE 1)

SET( SRC_H
	${SRC_H}
	${CUR_SRC}/Exceptions/Exceptions.h
	
	${CUR_SRC}/Exceptions/generalTestException.h
	${CUR_SRC}/Exceptions/nullFunctionException.h
	${CUR_SRC}/Exceptions/unknownException.h
)
SET( SRC_CPP
	${SRC_CPP}
	${CUR_SRC}/Exceptions/Exceptions.cpp
)
ENDIF(NOT UNITTEST_LIB_EXCEPTIONS_CMAKE)