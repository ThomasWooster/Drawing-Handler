#include "mesh.h"
#include <gl_core_4_4.h>


namespace tom
{

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
    }

    /**************************************************************************************************************************************
    **************************************************************************************************************************************/

    void Mesh::initiliseQuad()
    {
        // check that the mesh is not inited already 
        assert(vao == 0);

        //generate buffers
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        //bind vertex array AKA a mkesh wrapper
        glBindVertexArray(vao);

        //bind vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        //define 6 vertixes for 2 triangles
        Vertex vertices[6];
        vertices[0].position = { -0.5f, 0, 0.5f, 1 };
        vertices[1].position = { 0.5f, 0, 0.5f, 1 };
        vertices[2].position = { -0.5f, 0, -0.5f, 1 };
        vertices[3].position = { -0.5f, 0, -0.5f, 1 };
        vertices[4].position = { 0.5f, 0, 0.5f, 1 };
        vertices[5].position = { 0.5f, 0, -0.5f, 1 };

        // puits textures in 
        vertices[0].texCoord = { 0, 1 }; // bottem left
        vertices[1].texCoord = { 1, 1 }; // bottom right
        vertices[2].texCoord = { 0, 0 }; // top left

        vertices[3].texCoord = { 0, 0 }; // top left
        vertices[4].texCoord = { 1, 1 }; // bottom right
        vertices[5].texCoord = { 1, 0 }; // top right

        // adds normals to mesh
        vertices[0].normal = { 0, 1, 0, 0 };
        vertices[1].normal = { 0, 1, 0, 0 };
        vertices[2].normal = { 0, 1, 0, 0 };
        vertices[3].normal = { 0, 1, 0, 0 };
        vertices[4].normal = { 0, 1, 0, 0 };
        vertices[5].normal = { 0, 1, 0, 0 };


        //fill vertex buffer 
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        //enable first element as position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        //enable seccond element as normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

        //enable third element as texture
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

        //unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //quad has 2 triangles
        triCount = 2;
    }

    /**************************************************************************************************************************************
    **************************************************************************************************************************************/

    void Mesh::initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount /*= 0*/, unsigned int* indices /*= nullptr*/)
    {
        assert(vao == 0);

        // generate buffers
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        // bind vertex array AKA a mesh wrapper
        glBindVertexArray(vao);

        // bind vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);


        // fill the vertex buffer
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        //enable the first element as a position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        //enable seccond element as normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

        //enable third element as texture
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

        if (indexCount != 0)
        {
            glGenBuffers(1, &ibo);

            // bind the vertex buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            // fill the vertex buffer
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

            triCount = indexCount / 3;
        }
        else
        {
            triCount = vertexCount / 3;
        }

        // unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    /**************************************************************************************************************************************
    **************************************************************************************************************************************/

    void Mesh::initialiseFullscreenQuad()
    {
        assert(vao == 0);

        // generate buffers
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        // bind vertex array aka mesh wrapper
        glBindVertexArray(vao);

        // bind the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // define verticies
        float vertices[] = {
            -1, 1, // left top
            -1, -1, // left bottom
            1, 1, // right top
            -1, -1, // left bottom
            1, -1, // right bottom
            1, 1 // right top
        };

        // fill vertex buffer
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

        // enable first element as position 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);

        // unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // quad has 2 triangles
        triCount = 2;
    }

    void Mesh::initializeCube() /////////////// still needs setting up for cube rather than quad
    {
        // check that the mesh is not inited already 
        assert(vao == 0);

        //generate buffers
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        //bind vertex array AKA a mkesh wrapper
        glBindVertexArray(vao);

        //bind vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        //define 6 vertixes for 2 triangles
        Vertex vertices[36];
        // bottom face
        vertices[0].position = { -0.5f, -0.5f, 0.5f, 1 };
        vertices[1].position = { -0.5f, -0.5f, -0.5f, 1 };
        vertices[2].position = { 0.5f, -0.5f, 0.5f, 1 };
        vertices[3].position = { -0.5f, -0.5f, -0.5f, 1 };
        vertices[4].position = { 0.5f, -0.5f, -0.5f, 1 };
        vertices[5].position = { 0.5f, -0.5f, 0.5f, 1 };
        // topface
        vertices[6].position = { -0.5f, 0.5f, 0.5f, 1 };
        vertices[7].position = { 0.5f, 0.5f, 0.5f, 1 };
        vertices[8].position = { -0.5f, 0.5f, -0.5f, 1 };
        vertices[9].position = { -0.5f, 0.5f, -0.5f, 1 };
        vertices[10].position = { 0.5f, 0.5f, 0.5f, 1 };
        vertices[11].position = { 0.5f, 0.5f, -0.5f, 1 };
        // front face
        vertices[12].position = { -0.5f, 0.5f, -0.5f, 1 };
        vertices[13].position = { 0.5f, 0.5f, -0.5f, 1 };
        vertices[14].position = { -0.5f, -0.5f, -0.5f, 1 };
        vertices[15].position = { -0.5f, -0.5f, -0.5f, 1 };
        vertices[16].position = { 0.5f, 0.5f, -0.5f, 1 };
        vertices[17].position = { 0.5f, -0.5f, -0.5f, 1 };
        // back face
        vertices[18].position = { -0.5f, 0.5f, 0.5f, 1 };
        vertices[19].position = { -0.5f, -0.5f, 0.5f, 1 };
        vertices[20].position = { 0.5f, 0.5f, 0.5f, 1 };
        vertices[21].position = { -0.5f, -0.5f, 0.5f, 1 };
        vertices[22].position = { 0.5f, -0.5f, 0.5f, 1 };
        vertices[23].position = { 0.5f, 0.5f, 0.5f, 1 };
        // right face
        vertices[24].position = { -0.5f, 0.5f, -0.5f, 1 };
        vertices[25].position = { -0.5f, -0.5f, -0.5f, 1 };
        vertices[26].position = { -0.5f, 0.5f, 0.5f, 1 };
        vertices[27].position = { -0.5f, -0.5f, -0.5f, 1 };
        vertices[28].position = { -0.5f, -0.5f, 0.5f, 1 };
        vertices[29].position = { -0.5f, 0.5f, 0.5f, 1 };
        // left face
        vertices[30].position = { 0.5f, 0.5f, -0.5f, 1 };
        vertices[31].position = { 0.5f, 0.5f, 0.5f, 1 };
        vertices[32].position = { 0.5f, -0.5f, -0.5f, 1 };
        vertices[33].position = { 0.5f, -0.5f, -0.5f, 1 };
        vertices[34].position = { 0.5f, 0.5f, 0.5f, 1 };
        vertices[35].position = { 0.5f, -0.5f, 0.5f, 1 };

        // puits textures in 
        // bottom face
        vertices[0].texCoord = { 0, 1 }; // bottem left
        vertices[1].texCoord = { 1, 1 }; // bottom right
        vertices[2].texCoord = { 0, 0 }; // top left

        vertices[3].texCoord = { 0, 0 }; // top left
        vertices[4].texCoord = { 1, 1 }; // bottom right
        vertices[5].texCoord = { 1, 0 }; // top right

        // top face
        vertices[6].texCoord = { 0, 1 }; // bottem left
        vertices[7].texCoord = { 1, 1 }; // bottom right
        vertices[8].texCoord = { 0, 0 }; // top left

        vertices[9].texCoord = { 0, 0 }; // top left
        vertices[10].texCoord = { 1, 1 }; // bottom right
        vertices[11].texCoord = { 1, 0 }; // top right

        // front face
        vertices[12].texCoord = { 0, 1 }; // bottem left
        vertices[13].texCoord = { 1, 1 }; // bottom right
        vertices[14].texCoord = { 0, 0 }; // top left

        vertices[15].texCoord = { 0, 0 }; // top left
        vertices[16].texCoord = { 1, 1 }; // bottom right
        vertices[17].texCoord = { 1, 0 }; // top right

        // back face
        vertices[18].texCoord = { 0, 1 }; // bottem left
        vertices[19].texCoord = { 1, 1 }; // bottom right
        vertices[20].texCoord = { 0, 0 }; // top left

        vertices[21].texCoord = { 0, 0 }; // top left
        vertices[22].texCoord = { 1, 1 }; // bottom right
        vertices[23].texCoord = { 1, 0 }; // top right

        // right face
        vertices[24].texCoord = { 0, 1 }; // bottem left
        vertices[25].texCoord = { 1, 1 }; // bottom right
        vertices[26].texCoord = { 0, 0 }; // top left

        vertices[27].texCoord = { 0, 0 }; // top left
        vertices[28].texCoord = { 1, 1 }; // bottom right
        vertices[29].texCoord = { 1, 0 }; // top right

        // left face
        vertices[30].texCoord = { 0, 1 }; // bottem left
        vertices[31].texCoord = { 1, 1 }; // bottom right
        vertices[32].texCoord = { 0, 0 }; // top left

        vertices[33].texCoord = { 0, 0 }; // top left
        vertices[34].texCoord = { 1, 1 }; // bottom right
        vertices[35].texCoord = { 1, 0 }; // top right

        // adds normals to mesh
        // bottom face
        vertices[0].normal = { 0, -1, 0, 0 };
        vertices[1].normal = { 0, -1, 0, 0 };
        vertices[2].normal = { 0, -1, 0, 0 };
        vertices[3].normal = { 0, -1, 0, 0 };
        vertices[4].normal = { 0, -1, 0, 0 };
        vertices[5].normal = { 0, -1, 0, 0 };
        //top face
        vertices[6].normal = { 0, 1, 0, 0 };
        vertices[7].normal = { 0, 1, 0, 0 };
        vertices[8].normal = { 0, 1, 0, 0 };
        vertices[9].normal = { 0, 1, 0, 0 };
        vertices[10].normal = { 0, 1, 0, 0 };
        vertices[11].normal = { 0, 1, 0, 0 };
        //front face
        vertices[12].normal = { 0, 0, -1, 0 };
        vertices[13].normal = { 0, 0, -1, 0 };
        vertices[14].normal = { 0, 0, -1, 0 };
        vertices[15].normal = { 0, 0, -1, 0 };
        vertices[16].normal = { 0, 0, -1, 0 };
        vertices[17].normal = { 0, 0, -1, 0 };
        //back face
        vertices[18].normal = { 0, 0, 1, 0 };
        vertices[19].normal = { 0, 0, 1, 0 };
        vertices[20].normal = { 0, 0, 1, 0 };
        vertices[21].normal = { 0, 0, 1, 0 };
        vertices[22].normal = { 0, 0, 1, 0 };
        vertices[23].normal = { 0, 0, 1, 0 };
        // right face
        vertices[24].normal = { -1, 0, 0, 0 };
        vertices[25].normal = { -1, 0, 0, 0 };
        vertices[26].normal = { -1, 0, 0, 0 };
        vertices[27].normal = { -1, 0, 0, 0 };
        vertices[28].normal = { -1, 0, 0, 0 };
        vertices[29].normal = { -1, 0, 0, 0 };
        // left face
        vertices[30].normal = { 1, 0, 0, 0 };
        vertices[31].normal = { 1, 0, 0, 0 };
        vertices[32].normal = { 1, 0, 0, 0 };
        vertices[33].normal = { 1, 0, 0, 0 };
        vertices[34].normal = { 1, 0, 0, 0 };
        vertices[35].normal = { 1, 0, 0, 0 };

        //fill vertex buffer 
        glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        //enable first element as position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        //enable seccond element as normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

        //enable third element as texture
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

        //unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //quad has 2 triangles
        triCount = 12;
    }

    /**************************************************************************************************************************************
    **************************************************************************************************************************************/

    void Mesh::draw()
    {
        glBindVertexArray(vao);
        //using indecies or just verticies?
        if (ibo != 0)
        {
            glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
        }
    }

}