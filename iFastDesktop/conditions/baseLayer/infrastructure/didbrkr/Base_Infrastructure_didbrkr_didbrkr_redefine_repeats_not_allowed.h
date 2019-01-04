﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_redefine_repeats_not_allowed : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_redefine_repeats_not_allowed() { }
		~CBase_Infrastructure_didbrkr_didbrkr_redefine_repeats_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REDEFINE_REPEATS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error redefining field. Redefining dataset %dataset% contains a repeatable component, %comp%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error redefining field. Redefining dataset %dataset% contains a repeatable component, %comp%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler beim Redefinieren des Feldes. Die Redefinition des Datensatzes %dataset% enthält eine wiederholbare Komponente, %comp%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al redefinir el campo. El conjunto de datos de redefinición %dataset% contiene un componente repetible, %comp%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de redéfinition du champ. L'ensemble de données de redéfinition %dataset% comporte un élément qui peut être répété : %comp%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij het opnieuw definiëren van veld. Opnieuw te definiëren gegevensset %dataset% bevat een herhaalbare component, %comp%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



