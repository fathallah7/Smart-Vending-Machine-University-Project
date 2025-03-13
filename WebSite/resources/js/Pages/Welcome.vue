<script setup>
import { Head, Link } from '@inertiajs/vue3';
import GuestLayout from '@/Layouts/GuestLayout.vue';
defineOptions({ layout: GuestLayout });

defineProps({
    canLogin: {
        type: Boolean,
    },
    canRegister: {
        type: Boolean,
    },
    laravelVersion: {
        type: String,
        required: true,
    },
    phpVersion: {
        type: String,
        required: true,
    },
});


function pepsi() {
    fetch('https://testv-a9639-default-rtdb.europe-west1.firebasedatabase.app/test.json', {
        method: 'PATCH',
        body: JSON.stringify({ pepsi: 1 }),
        headers: {
            'Content-Type': 'application/json'
        }
    })
}
function cola() {
    fetch('https://testv-a9639-default-rtdb.europe-west1.firebasedatabase.app/test.json', {
        method: 'PATCH',
        body: JSON.stringify({ cola: 1 }),
        headers: {
            'Content-Type': 'application/json'
        }
    })
}
function sup() {
    fetch('https://testv-a9639-default-rtdb.europe-west1.firebasedatabase.app/test.json', {
        method: 'PATCH',
        body: JSON.stringify({ "7up": 1 }),
        headers: {
            'Content-Type': 'application/json'
        }
    })
}

import { ref, computed } from 'vue';

const questionsAndAnswers = ref([
    {
        question: "من هو مستشار وزير التعليم العالي؟",
        answers: [
            "أ.د أحمد منيب الصباغ",
            "د طارق شوقي"
        ],
        correctAnswer: "أ.د أحمد منيب الصباغ",
    },
    {
        question: "أين تقع جامعة برج العرب",
        answers: [
            "برج الاجانب",
            "برج العرب"
        ],
        correctAnswer:
            "برج العرب",
    },
    {
        question: "في أي عام أنشئت جامعة برج العرب",
        answers: [
            "عام 2000",
            "عام 2022"
        ],
        correctAnswer:
            "عام 2022"
    },
    // Add more questions and answers as needed
]);

const currentIndex = ref(0);
const itemsPerPage = ref(1);
const score = ref(0);
const passed = ref(false);
const failed = ref(false);

const displayedQAs = computed(() => {
    return questionsAndAnswers.value.slice(currentIndex.value, currentIndex.value + itemsPerPage.value);
});

const chooseAnswer = (answer) => {
    // Check if the selected answer is correct
    if (answer === questionsAndAnswers.value[currentIndex.value].correctAnswer) {
        score.value++;
    }

    // Move to the next question or end the quiz
    if (currentIndex.value < questionsAndAnswers.value.length - 1) {
        currentIndex.value++;
    } else {
        // Calculate the score percentage
        const scorePercentage = (score.value / questionsAndAnswers.value.length) * 100;
        // Check if the user has passed
        if (scorePercentage > 50) {
            passed.value = true;
        } else {
            failed.value = true;
        }
        // Optionally, you can handle the end of the quiz here
        console.log('All questions answered. Passed:', passed.value);
    }
};


</script>

<template>

    <Head title="Welcome" />

    <div class="w-full md:w-2/3 mx-auto p-5 bg-white rounded-lg shadow" v-if="!passed && !failed">
        <div class="text-left" style="direction: rtl; ">

            أجب عن الأسئلة الاتية وفز معنا بمياه غازية !! ☺☺

        </div>



        <div class="mt-8 space-y-8">
            <div v-for="(qa, index) in displayedQAs" :key="index" style="direction: rtl;"
                class="p-6 bg-white rounded-lg shadow">
                <div class="flex items-start">
                    <div>
                        <span
                            class="inline-flex justify-center items-center w-6 h-6 mx-5 rounded bg-green-500 text-white font-medium text-sm">
                            Q
                        </span>
                    </div>

                    <p class="ml-4 md:ml-6 text-bold">
                        {{ qa.question }}
                    </p>
                </div>

                <div class="mt-3">
                    <div class="flex items-start" v-for="(answer, index) in qa.answers" :key="index">
                        <div>
                            <span
                                class="inline-flex justify-center items-center w-6 h-6 mx-5 rounded bg-gray-200 text-gray-800 font-medium text-sm">
                                {{ index }}
                            </span>
                        </div>

                        <p class="ml-4 md:ml-6 text-bold text-gray-800" @click="chooseAnswer(answer)">
                            {{ answer }}
                        </p>
                    </div>
                </div>



            </div>
        </div>
    </div>

    <section v-if="passed && !failed"
        class="grid grid-cols-1 lg:grid-cols-3 items-center justify-center gap-10 bg-slate-50 py-12 px-6 dark:bg-slate-900 md:grid-cols-2">
        <div @click="pepsi"
            class="block cursor-pointer  rounded-lg bg-white text-surface shadow-secondary-1 dark:bg-surface-dark dark:text-white justify-center">
            <div class="relative overflow-hidden bg-cover bg-no-repeat">
                <img class="rounded-t-lg" src="images/pepsi.png" style="height: 300px;" alt="" />
            </div>
            <div class="p-6">
                <p class="text-base text-center">
                    pepsi
                </p>
            </div>
        </div>
        <div @click="cola"
            class="block cursor-pointer  rounded-lg bg-white text-surface shadow-secondary-1 dark:bg-surface-dark dark:text-white">
            <div class="relative overflow-hidden bg-cover bg-no-repeat">
                <img class="rounded-t-lg" src="images/cola.png" style="height: 300px" alt="" />
            </div>
            <div class="p-6">
                <p class="text-base text-center">
                    cola
                </p>
            </div>
        </div>
        <div @click="sup"
            class="block rounded-lg cursor-pointer bg-white text-surface shadow-secondary-1 dark:bg-surface-dark dark:text-white">
            <div class="relative overflow-hidden bg-cover bg-no-repeat">
                <img class="rounded-t-lg" src="images/7up.png" style="height: 300px" alt="" />
            </div>
            <div class="p-6">
                <p class="text-base text-center">
                    7up
                </p>
            </div>
        </div>
    </section>

    <div v-if="failed">
        <div style="font-size: xx-large;"
            class="text-center p-4 mb-4 text-xxl text-yellow-800 rounded-lg bg-yellow-50 dark:bg-gray-800 dark:text-yellow-300"
            role="alert">
            <span class="font-medium">للأسف</span> حظ أوفر المرة القادمة
        </div>
    </div>
    <section class="container mx-auto px-8 py-28 sm:px-12">
        <h1 class="sm:mb-18 mb-24 w-full text-center text-4xl font-bold dark:text-slate-50 sm:mx-auto sm:w-4/5">
            Your favorite cafe in town
        </h1>
        <div class="grid grid-cols-2 gap-4 md:grid-cols-3">
            <div
                class="flex cursor-pointer flex-col items-center justify-start rounded-lg bg-slate-50 py-5 px-6 text-center text-slate-800 shadow-slate-200 transition hover:bg-white hover:shadow-lg hover:shadow-slate-200 dark:bg-slate-800 dark:text-slate-200 dark:shadow-slate-700 dark:hover:shadow-slate-800">
                <svg preserveAspectRatio="xMidYMid meet" viewBox="0 0 24 24" width="1.2em" height="1.2em"
                    class="h-8 w-8">
                    <g fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round"
                        stroke-width="2">
                        <path d="M12 18h.01m-2.838-2.828a4 4 0 0 1 5.656 0m-8.485-2.829a8 8 0 0 1 11.314 0"></path>
                        <path d="M3.515 9.515c4.686-4.687 12.284-4.687 17 0"></path>
                    </g>
                </svg>
                <div class="mt-3 text-sm font-semibold">Convenient Payments
                </div>
            </div>
            <div
                class="flex cursor-pointer flex-col items-center justify-start rounded-lg bg-slate-50 py-5 px-6 text-center text-slate-800 shadow-slate-200 transition hover:bg-white hover:shadow-lg hover:shadow-slate-200 dark:bg-slate-800 dark:text-slate-200 dark:shadow-slate-700 dark:hover:shadow-slate-800">
                <svg preserveAspectRatio="xMidYMid meet" viewBox="0 0 24 24" width="1.2em" height="1.2em"
                    class="h-8 w-8">
                    <g fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round"
                        stroke-width="2">
                        <path d="M12 18h.01m-2.838-2.828a4 4 0 0 1 5.656 0m-8.485-2.829a8 8 0 0 1 11.314 0"></path>
                        <path d="M3.515 9.515c4.686-4.687 12.284-4.687 17 0"></path>
                    </g>
                </svg>
                <div class="mt-3 text-sm font-semibold">Remote Monitoring
                </div>
            </div>
            <div
                class="flex cursor-pointer flex-col items-center justify-start rounded-lg bg-slate-50 py-5 px-6 text-center text-slate-800 shadow-slate-200 transition hover:bg-white hover:shadow-lg hover:shadow-slate-200 dark:bg-slate-800 dark:text-slate-200 dark:shadow-slate-700 dark:hover:shadow-slate-800">
                <svg preserveAspectRatio="xMidYMid meet" viewBox="0 0 24 24" width="1.2em" height="1.2em"
                    class="h-8 w-8">
                    <g fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round"
                        stroke-width="2">
                        <path d="M12 18h.01m-2.838-2.828a4 4 0 0 1 5.656 0m-8.485-2.829a8 8 0 0 1 11.314 0"></path>
                        <path d="M3.515 9.515c4.686-4.687 12.284-4.687 17 0"></path>
                    </g>
                </svg>
                <div class="mt-3 text-sm font-semibold">Inventory Management
                </div>
            </div>
            <div
                class="flex cursor-pointer flex-col items-center justify-start rounded-lg bg-slate-50 py-5 px-6 text-center text-slate-800 shadow-slate-200 transition hover:bg-white hover:shadow-lg hover:shadow-slate-200 dark:bg-slate-800 dark:text-slate-200 dark:shadow-slate-700 dark:hover:shadow-slate-800">
                <svg preserveAspectRatio="xMidYMid meet" viewBox="0 0 24 24" width="1.2em" height="1.2em"
                    class="h-8 w-8">
                    <path fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round"
                        stroke-width="2"
                        d="M3 14a1 1 0 0 1 1-1h16a1 1 0 0 1 1 1v2a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1zm5-1v4m8-12v.5a2 2 0 0 0 2 2a2 2 0 0 1 2 2v.5">
                    </path>
                </svg>
                <div class="mt-3 text-sm font-semibold">Real-time Notifications
                </div>
            </div>
            <div
                class="flex cursor-pointer flex-col items-center justify-start rounded-lg bg-slate-50 py-5 px-6 text-center text-slate-800 shadow-slate-200 transition hover:bg-white hover:shadow-lg hover:shadow-slate-200 dark:bg-slate-800 dark:text-slate-200 dark:shadow-slate-700 dark:hover:shadow-slate-800">
                <svg preserveAspectRatio="xMidYMid meet" viewBox="0 0 24 24" width="1.2em" height="1.2em"
                    class="h-8 w-8">
                    <g fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round"
                        stroke-width="2">
                        <path d="M20 6v12a2 2 0 0 1-2 2H8a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h10a2 2 0 0 1 2 2zM10 16h6">
                        </path>
                        <path d="M11 11a2 2 0 1 0 4 0a2 2 0 1 0-4 0M4 8h3m-3 4h3m-3 4h3"></path>
                    </g>
                </svg>
                <div class="mt-3 text-sm font-semibold">User Personalization
                </div>
            </div>
            <div
                class="flex cursor-pointer flex-col items-center justify-start rounded-lg bg-slate-50 py-5 px-6 text-center text-slate-800 shadow-slate-200 transition hover:bg-white hover:shadow-lg hover:shadow-slate-200 dark:bg-slate-800 dark:text-slate-200 dark:shadow-slate-700 dark:hover:shadow-slate-800">
                <svg preserveAspectRatio="xMidYMid meet" viewBox="0 0 24 24" width="1.2em" height="1.2em"
                    class="h-8 w-8">
                    <g fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round"
                        stroke-width="2">
                        <path d="M4 6a2 2 0 0 1 2-2h12a2 2 0 0 1 2 2v12a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2z"></path>
                        <path d="M9 16V8h4a2 2 0 0 1 0 4H9"></path>
                    </g>
                </svg>
                <div class="mt-3 text-sm font-semibold">Enhanced Security</div>
            </div>
        </div>
    </section>





</template>

<style>
.bg-dots-darker {
    background-image: url("data:image/svg+xml,%3Csvg width='30' height='30' viewBox='0 0 30 30' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='M1.22676 0C1.91374 0 2.45351 0.539773 2.45351 1.22676C2.45351 1.91374 1.91374 2.45351 1.22676 2.45351C0.539773 2.45351 0 1.91374 0 1.22676C0 0.539773 0.539773 0 1.22676 0Z' fill='rgba(0,0,0,0.07)'/%3E%3C/svg%3E");
}

@media (prefers-color-scheme: dark) {
    .dark\:bg-dots-lighter {
        background-image: url("data:image/svg+xml,%3Csvg width='30' height='30' viewBox='0 0 30 30' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='M1.22676 0C1.91374 0 2.45351 0.539773 2.45351 1.22676C2.45351 1.91374 1.91374 2.45351 1.22676 2.45351C0.539773 2.45351 0 1.91374 0 1.22676C0 0.539773 0.539773 0 1.22676 0Z' fill='rgba(255,255,255,0.07)'/%3E%3C/svg%3E");
    }
}
</style>
