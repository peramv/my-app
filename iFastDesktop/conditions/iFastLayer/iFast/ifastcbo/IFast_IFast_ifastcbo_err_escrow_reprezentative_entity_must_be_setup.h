#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrow_reprezentative_entity_must_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrow_reprezentative_entity_must_be_setup() { }
		~CIFast_IFast_ifastcbo_err_escrow_reprezentative_entity_must_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROW_REPREZENTATIVE_ENTITY_MUST_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow Representative Entity must be setup for Escrow Account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Escrow Reprezentative Entity must be setup for Escrow Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Escrow-Repräsentant-Objekt muss für ein Escrow-(Ander)konto erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse entidad Representante de custodia para la cuenta de custodia")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le cessionnaire doit être créé pour le compte cédé en garantie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid pandvertegenwoordiger moet worden ingesteld voor het pandaccount")); }

        // Actions
	};
}



