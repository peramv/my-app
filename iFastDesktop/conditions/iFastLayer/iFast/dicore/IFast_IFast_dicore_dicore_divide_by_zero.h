#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_divide_by_zero : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_divide_by_zero() { }
		~CIFast_IFast_dicore_dicore_divide_by_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DIVIDE_BY_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Controls name record Entity ID not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Controls name record Entity ID not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontroll-Namenseintrag EntityID nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la identificación de entidad del registro de nombre de controles")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'entité de l'enregistrement du nom des contrôles est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Naam besturingrecord EntityID is niet gevonden")); }

        // Actions
	};
}



