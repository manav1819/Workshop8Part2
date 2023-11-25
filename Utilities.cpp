// Workshop 8 - Smart Pointers
/*
 *****************************************************************
 * Name: Manav Patel                                             *
 * Email: patmanav@sheridancollege.ca                            *
 * Student Id: 991500582                                         *
 * Date: 23-11-2023                                              *
 *                                                               *
 *****************************************************************
*/
#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		//
        for (size_t i = 0; i < allProfiles.size(); ++i) {
            const Profile& currentProfile = allProfiles[i];

            bool isBanned = false;
            for (size_t j = 0; j < bannedProfiles.size(); ++j) {
                if (currentProfile.m_name.first_name == bannedProfiles[j].m_name.first_name &&
                    currentProfile.m_name.last_name == bannedProfiles[j].m_name.last_name &&
                    currentProfile.m_age == bannedProfiles[j].m_age) {
                    isBanned = true;
                    break;
                }
            }

            if (!isBanned) {
                Profile* validatedProfile = new Profile(currentProfile.m_name, currentProfile.m_address, currentProfile.m_age);

                try {
                    validatedProfile->validateAddress();
                    result += validatedProfile;
                }
                catch (const std::exception& e) {
                    delete validatedProfile;
                    cerr << "Caught exception: " << e.what() << endl;
                }
            }
        }
        return result;
		
	}

	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;

        for (size_t i = 0; i < allProfiles.size(); ++i) {
            const Profile& currentProfile = allProfiles[i];

            bool isBanned = false;
            for (size_t j = 0; j < bannedProfiles.size(); ++j) {
                if (currentProfile.m_name.first_name == bannedProfiles[j].m_name.first_name &&
                    currentProfile.m_name.last_name == bannedProfiles[j].m_name.last_name &&
                    currentProfile.m_age == bannedProfiles[j].m_age) {
                    isBanned = true;
                    break;
                }
            }

            if (!isBanned) {
                unique_ptr<Profile> validatedProfile = make_unique<Profile>(currentProfile.m_name, currentProfile.m_address, currentProfile.m_age);

                try {
                    validatedProfile->validateAddress();
                    result += validatedProfile.get();
                    validatedProfile.release();
                }
                catch (const std::exception& e) {
                    cerr << "Caught exception: " << e.what() << endl;
                }

            }
        }
        return result;
    }
}
