ROOTDIR=..
OUTDIR=$(ROOTDIR)/dataimpl
INTDIR=$(ROOTDIR)/dataimpl
DBDIR=$(ROOTDIR)/data

TIMBUK3=..\core\3rdparty\bin\timbuk3.exe
TIMBUK3_PROJ=$(INTDIR)/ifast.ini

.SUFFIXES : .mdb .target

        
ALL : "$(OUTDIR)\ifast_dataimpl.target"

CLEAN :
        -@erase "$(OUTDIR)\ifast_dataimpl.target"
        
.mdb.target:
        @$(TIMBUK3) -i$(TIMBUK3_PROJ)

"$(OUTDIR)/ifast_dataimpl.target": "$(DBDIR)/ifast_fields.mdb" "$(INTDIR)/ifast.ini" "$(TIMBUK3)" "$(ROOTDIR)/core/bfdata/timbuk3.hpp"
	if DEFINED _JOBSTATUSFILE echo Generating from DataDictionary > %_JOBSTATUSFILE% nul
        @$(TIMBUK3) -i$(TIMBUK3_PROJ) 






    


