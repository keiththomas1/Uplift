#include "coreds.h"

void CoreDS::AddExercise(Exercise *ex) {
    m_exercise_id_map.insert(ExerciseIDPair(ex->GetExerciseID(), ex));
    m_exercise_string_map.insert(ExerciseStringPair(ex->GetName(), ex));

}

Exercise* CoreDS::GetExercise(int ID) {
    ExerciseIDMap::iterator m_it = m_exercise_id_map.find(ID);
    if (m_it == m_exercise_id_map.end()) {
        printf("returning null\n");
        return NULL;
    }
    else {
        return m_it->second; //second location in pair
    }
}

void CoreDS::PrintExerciseList() {
    for (ExerciseNameIDMap::iterator m_it = m_exerciseName_id_map.begin();
         m_it != m_exerciseName_id_map.end();
         m_it++) {
        printf("%s\t%d\n", m_it->first.c_str(), m_it->second);
    }
        //printf("%s\n", m_it->second->GetName().c_str());
}

void CoreDS::PrintExerciseObjects() {
    for (ExerciseIDMap::iterator m_it = m_exercise_id_map.begin();
         m_it != m_exercise_id_map.end();
         m_it++) {
        printf("%s\t\t%d reps @ %dlbs\n", m_it->second->GetName().c_str(), m_it->second->GetReps(),
               m_it->second->GetWeight());
    }
}

int CoreDS::GetExerciseIDFromName(string name) {
    ExerciseNameIDMap::iterator m_it = m_exerciseName_id_map.find(name);
    if (m_it == m_exerciseName_id_map.end()) {
       return -1; //exercise not found
    }
    return m_it->second;
}

//TODO: case checking (only first letter is capitalized)
void CoreDS::AddToExercisesList(string name) {
    pair<map<string, int>::iterator, bool> ret;
    ret = m_exerciseName_id_map.insert(ExerciseNameIDPair(name, GetNextExerciseNameID()));
    if (ret.second == false) {
        cout << "This exercise already exists!" << endl;
        GetPrevExerciseNameID(); //go back one exerciseName ID
    }
}
