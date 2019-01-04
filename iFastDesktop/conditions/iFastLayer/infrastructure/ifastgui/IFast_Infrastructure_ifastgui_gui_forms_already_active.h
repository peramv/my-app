#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_forms_already_active : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_forms_already_active() { }
		~CIFast_Infrastructure_ifastgui_gui_forms_already_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_FORMS_ALREADY_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem: return severe error. Check CICS error logs for more information.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem: return severe error. Check CICS error logs for more information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Schwerer Fehler zurückgegeben. Mehr Informationen finden Sie in den CICS-Fehleraufzeichnungen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno: el sistema devolvió un error grave. Verifique los registros de error CICS para más información.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne : grave erreur de renvoi. Vérifiez les enregistrements d'erreur CICS pour plus d'information.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem: ernstige fout retour. Raadpleeg het CICS-foutenlogboek voor meer informatie")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



