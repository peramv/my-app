#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_vm_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_vm_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_vm_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VM_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Forms cannot create OLE class factory.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Forms cannot create OLE class factory.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Formulare können OLE-Klassengruppe nicht erstellen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los formularios no pueden crear fábrica de clase OLE.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les formulaires ne peuvent créer une classe d'objets de classe OLE.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Formulieren kunnen geen OLE ?class factory? maken")); }

        // Actions
	};
}



