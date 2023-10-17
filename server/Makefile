NAME = tpe_server

CXX = g++
CXXFLAGS = 

SRC = main.cpp \
	  create_bmp.cpp \
	  main.cpp \
	  permutation.cpp \
	  save_bmp_data.cpp \
	  substitution.cpp \
	  create_random_n_arr.cpp \
	  my_join.cpp \
	  recv_data_from_client.cpp \
	  send_data_to_client.cpp \
	  tpe.cpp \
	  init_bmp_header.cpp \
	  my_strtrim.cpp \
	  round.cpp \
	  server.cpp \
	  preprocess.cpp

OBJ = $(SRC:.cpp=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
