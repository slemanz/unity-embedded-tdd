CC = gcc
CFLAGS = -c -Wall -Wextra -std=gnu99 -g -O0

BUILD_DIR = build
SRC_DIR   = src
TEST_DIR  = tests
UNITY_DIR = unity

###########################################
#                INCLUDES
###########################################

INCLUDES += -I $(UNITY_DIR)
INCLUDES += -I $(SRC_DIR)
INCLUDES += -I $(TEST_DIR)

############################################
#               SOURCE FILES
############################################

# Production code under test
OBJS      += $(BUILD_DIR)/registry.o
OBJS      += $(BUILD_DIR)/gpio_reg.o
OBJS      += $(BUILD_DIR)/sensor.o

# Test cases and the runner
TEST_OBJS += $(BUILD_DIR)/registry_test.o
TEST_OBJS += $(BUILD_DIR)/gpio_reg_test.o
TEST_OBJS += $(BUILD_DIR)/sensor_test.o
TEST_OBJS += $(BUILD_DIR)/AllTestRunner.o

# Unity framework
UNITY     += $(BUILD_DIR)/unity.o
UNITY     += $(BUILD_DIR)/unity_fixture.o

all: $(BUILD_DIR) $(BUILD_DIR)/run_tests

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(BUILD_DIR)/run_tests: $(TEST_OBJS) $(OBJS) $(UNITY)
	$(CC) -o $@ $^
	./$@

clean:
	rm -rf $(BUILD_DIR)/*
