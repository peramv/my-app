#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_extra_lines_in_properties_file : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_extra_lines_in_properties_file() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_extra_lines_in_properties_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_EXTRA_LINES_IN_PROPERTIES_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Properties file %file% has extra lines at the end.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Properties file %file% has extra lines at the end.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eigenschaftendatei %file% hat zusätzliche Zeilen am Ende.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El archivo de propiedades %file% tiene líneas adicionales al final.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a des lignes supplémentaires à la fin du fichier des propriétés %file%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eigenschappenbestand %file% heeft extra regels op het einde")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check properties file")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



