#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_joint_entity_record_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_joint_entity_record_available() { }
		~CIFast_IFast_ifastdbrkr_err_no_joint_entity_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_JOINT_ENTITY_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Joint Entity record available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Joint Entity record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Gemeinsames-Objekt-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro de entidad conjunta disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'entité conjointe disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record voor gezamenlijke eenheid is niet beschikbaar")); }

        // Actions
	};
}



