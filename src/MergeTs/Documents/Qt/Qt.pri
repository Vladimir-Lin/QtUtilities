win32 {
basichelp.input        = $${PWD}/Essentials.qhp
basichelp.output       = $${PWD}/${QMAKE_FILE_BASE}.qch
basichelp.commands     = qhelpgenerator.exe ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
QMAKE_EXTRA_COMPILERS += basichelp
}

OTHER_FILES           += $${PWD}/*.qhp
OTHER_FILES           += $${PWD}/*.css
OTHER_FILES           += $${PWD}/*.html
OTHER_FILES           += $${PWD}/cn/*.html
OTHER_FILES           += $${PWD}/tw/*.html
