#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_dataset_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_dataset_not_found() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_dataset_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_DATASET_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The dataset %dataset% was not found in the repository file.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The dataset %dataset% was not found in the repository file.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Datensatz %dataset% wurde in der Lagerdatei nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el conjunto de datos %dataset% en el archivo de depósito.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'ensemble de données %dataset% est introuvable dans le fichier de référence.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevensset %dataset% is niet gevonden in het verzamelbestand")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check repository file.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check repository file.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Repositorydatei.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de depósito.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier de référence.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het verzamelbestand")); }
	};
}



