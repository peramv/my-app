#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_cannot_assign_data_objects : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_cannot_assign_data_objects() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_cannot_assign_data_objects() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_CANNOT_ASSIGN_DATA_OBJECTS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot assign data objects, properties %props1% and %props2% don't match.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot assign data objects, properties %props1% and %props2% don't match.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenobjekte können nicht zugewiesen werden, die Eigenschaften %props1% und %props2% passen nicht zueinander.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se pueden asignar objetos de datos, las propiedades %props1% y %props2% no coinciden.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'attribuer les objets de données, les propriétés %props1% et %props2% ne correspondent pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevensobjecten kunnen niet worden toegekend, eigenschappen %props1% en %props2% komen niet overeen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



