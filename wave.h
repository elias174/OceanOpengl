#ifndef WAVE_H
#define WAVE_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

typedef struct // Definicion de un punto del terreo
{
    GLfloat s, t; // Coordenadas de texturas
    GLfloat nx, ny, nz; // Coordenadas de la normal
    GLfloat x, hauteur, z; // posición del vértice
} WPoint;


class Wave
{
public:
    GLfloat amplitude;
    GLfloat frequency;
    GLfloat direction;
    GLfloat phase;
    Wave(GLfloat amplitude, GLfloat frequency, GLfloat direction, GLfloat phase) {
        this->amplitude = amplitude;
        this->frequency = frequency;
        this->direction = direction;
        this->phase = phase;
    }
};


class Ocean
{
public:
    GLuint n_x, m_z;
    GLfloat size_x, size_z;
    int n_waves;
    WPoint *points;
    vector<GLuint> list_index;
    GLuint *pointer_list_index;
    vector<Wave> waves;

    GLfloat computeHeight(float x, float z, float t)
    {
        GLfloat height = 0.0;
        GLfloat k;
        for( int i=0; i< waves.size(); i++ )
        {
            k = 4.0 * M_PI * M_PI * waves[i].frequency * waves[i].frequency / 9.81;
            height += waves[i].amplitude * cos(k*(x*cos(waves [i].direction)+z*sin(waves[i].direction))-2.0f*M_PI* waves [i].frequency*t + waves [i].phase );
        }
        return height;
    }

    void update_heights(float t){
        for(int i=0; i<(m_z*n_x); i++){
            GLfloat h_temp = computeHeight(this->points[i].x, this->points[i].z, t);
            this->points[i].hauteur = abs(h_temp)/2.5;
            //cout << this->points[i].hauteur << endl;
        }
    }


    Ocean(GLuint n_x, GLuint m_z, GLfloat size_x, GLfloat size_z){
        this->n_x = n_x;
        this->m_z = m_z;
        this->size_x = size_x;
        this->size_z = size_z;
    }

    void load_waves(string archivo){
        std::ifstream infile(archivo.c_str());
        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            GLfloat a, b ,c;
            if (!(iss >> a >> b >> c)) { break; } // error
            Wave f(a,b,c,0);
            waves.push_back(f);
        }
    }

    void create_list_vertex(){
        this->points = new WPoint[n_x*m_z];
        int index_list = 0;
        for(GLfloat z=0.0; z<m_z; z += size_z){
            for(GLfloat x=0.0; x<n_x; x += size_x){
                this->points[index_list].x = x;
                this->points[index_list].hauteur = 1;
                this->points[index_list].z = z;

                this->points[index_list].nx = 0;
                this->points[index_list].ny = 0;
                this->points[index_list].nz = 1;

                this->points[index_list].s = 1;
                this->points[index_list].t = 1;
                index_list++;
            }
        }
    }

    void create_index_list(){
        GLuint size_list = (n_x*m_z)*3;
        int index_list = 0;
        GLuint index_pos = n_x;
        for(GLuint z=1; z<m_z; z++){
            GLuint old_index_pos = index_pos;
            for(GLuint x=0; x<n_x-1; x++){
                //                this->list_index[index_list] index_pos;
                //                this->list_index[index_list+1] = index_pos-(n_x-1);
                //                this->list_index[index_list+2] = (index_pos-(n_x-1))-1;

                //                this->list_index[index_list+3] = index_pos + 1;
                //                this->list_index[index_list+4] = (index_pos+1)-(n_x);
                //                this->list_index[index_list+5] = index_pos;

                this->list_index.push_back(index_pos);
                this->list_index.push_back(index_pos-(n_x-1));
                this->list_index.push_back((index_pos-(n_x-1))-1);

                this->list_index.push_back(index_pos + 1);
                this->list_index.push_back((index_pos+1)-(n_x));
                this->list_index.push_back(index_pos);
                index_pos += 1;
            }
            index_pos = old_index_pos;
            index_pos += n_x;
        }
        //        cout << endl << endl;
        //        cout << list_index.size() << endl << endl;
        //        for(int i=0;i<list_index.size();i++){
        //            cout << this->list_index[i] << ',';
        //        }
        //        cout << endl;
        this->pointer_list_index = &(this->list_index[0]);
    }

    void display(){
        glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(WPoint), &this->points[0].s);
        glDrawElements(GL_TRIANGLES, this->list_index.size() , GL_UNSIGNED_INT, (void*)this->pointer_list_index);
        glDisable(GL_COLOR_MATERIAL);
    }
};


#endif // WAVE_H
