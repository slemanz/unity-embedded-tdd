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

# Production code under test (note: the real gpio.c is never compiled,
# the mock provides GPIO_Write/GPIO_Read instead)
OBJS      += $(BUILD_DIR)/led_driver.o

# Test cases, the GPIO mock, and the runner
TEST_OBJS += $(BUILD_DIR)/test_led_driver.o
TEST_OBJS += $(BUILD_DIR)/mock_gpio.o
TEST_OBJS += $(BUILD_DIR)/test_runner.o

# Unity framework
UNITY     += $(BUILD_DIR)/unity.o

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
