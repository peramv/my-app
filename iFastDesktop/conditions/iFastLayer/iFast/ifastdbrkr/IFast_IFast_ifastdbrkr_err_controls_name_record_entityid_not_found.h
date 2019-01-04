#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_controls_name_record_entityid_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_controls_name_record_entityid_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_controls_name_record_entityid_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTROLS_NAME_RECORD_ENTITYID_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

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



